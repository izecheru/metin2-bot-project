#include "scanner.h"
#include <iostream>
#include <sstream>

std::vector<PatternScanner::PatternByte> PatternScanner::toBytes(const std::string& pattern)
{
  std::vector<PatternByte> patternBytes;
  std::istringstream stream(pattern);
  std::string token;

  while (stream >> token)
  {
    if (token == "??" || token.find('?') != std::string::npos)
    {
      patternBytes.push_back({ 0x00, true });
    }
    else
    {
      patternBytes.push_back({ static_cast<uint8_t>(std::stoul(token, nullptr, 16)), false });
    }
  }

  return patternBytes;
}

std::uint8_t* PatternScanner::scan(std::string& signature)
{
  auto module = GetModuleHandle(NULL);
  auto dosHeader = (PIMAGE_DOS_HEADER)module;
  auto ntHeaders =
    (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);

  auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
  auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

  // before we process the signature/pattern we must get the index of the rightmost wildcard
  // since the max shift is calculated using its index (wildcards match anything so yea)
  std::vector<PatternScanner::PatternByte> bytes = toBytes(signature);
  int max_index = bytes.size() - 1;
  int max_shift = bytes.size();
  int wildcard_index = 0;
  for (int i = 0; i < max_index; i++)
  {
    if (bytes[i].isWildcard)
    {
      // max shift is the position we are currently at in this for loop
      max_shift = max_index - i;
      wildcard_index = i;
    }
  }

  int shift_table[256];
  for (int i = 0; i < 256; i++)
  {
    shift_table[i] = max_shift;
  }

  for (int i = wildcard_index + 1; i < max_index; i++)
  {
    shift_table[bytes[i].value] = max_index - i;
  }

  for (int i = 0; i < bytes.size(); i++)
  {
    printf_s("i: %d -> value -> 0x%02x shift amount -> %d\n", i, bytes[i].value, shift_table[bytes[i].value]);
  }

  for (auto i = 0; i < sizeOfImage - max_shift;)
  {
    for (auto j = max_index; j >= 0; j--)
    {
      if (!bytes[j].isWildcard && scanBytes[i + j] != bytes[j].value)
      {
        i += shift_table[scanBytes[i + j]];
        break;
      }

      if (j == 0)
      {
        std::cout << "Found signature at address: 0x"
          << std::hex << reinterpret_cast<uintptr_t>(scanBytes + i) << std::dec << "\n";
        return (uint8_t*)(scanBytes + i);
      }
    }
  }

  std::cout << "Signature not found\n";

  return 0;
}