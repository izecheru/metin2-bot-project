# Metin2Bot

## This is a proof of concept; it is not intended for malicious use

So I implemeted boyer moore horspool or however is spelled.

Took inspiration from a video I found on youtube.

This is the struct used to process the pattern.
```c++
  struct PatternByte
  {
    uint8_t value;
    bool isWildcard;
  };

 std::vector<PatternScanner::PatternByte> PatternScanner::toBytes(const std::string& pattern)
{
  std::vector<PatternByte> patternBytes;
  std::istringstream stream(pattern);
  std::string token;

  while (stream >> token)
  {
    if (token == "?" || token.find('?') != std::string::npos)
    {
      // we use the bool because as far as I know any 0x value can
      // be interpreted, so a flag helps me skip the wildcard since
      // a wildcard can match with any value
      patternBytes.push_back({ 0x00, true });
    }
    else
    {
      // we turn it to a hexadecimal value and store it in the vector
      patternBytes.push_back({ static_cast<uint8_t>(std::stoul(token, nullptr, 16)), false });
    }
  }

  return patternBytes;
}

```

A part of the function is here
```c++
 std::vector<PatternScanner::PatternByte> bytes = toBytes(signature);
  int max_index = bytes.size() - 1;
  int max_shift = bytes.size();
  int wildcard_index = 0;
  for (int i = 0; i < max_index; i++)
  {
    // if we have a wildcard then we don't update the shift value
    // since it matches anything
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

  // we update the shift value only for the bytes to the right of the
  // rightmost wildcard
  for (int i = wildcard_index + 1; i < max_index; i++)
  {
    shift_table[bytes[i].value] = max_index - i;
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

```

So a bit of explanation as of why we update the shift values ONLY starting right after the rightmost wildcard.
```c++
pattern: c?ef (size = 4) (max_index = 3) (max shift = max index - wildcard index = 3-1 = 2)
the distance from end to the rightmost wildcard is 2!!!
shift table: {2,2,1,2}
text: abcdefghijkl
0 1 2 3 4 5 6 7 8 9 10 11
a b c d e f g h i j k  l
c ? e f

If we were to go the traditional way of shifting, we would miss the match by
going too far to the right.(shifting by size = 4)
0 1 2 3 4 5 6 7 8 9 10 11
a b c d e f g h i j k  l
        c ? e f

Since a wildcard can match anything we move so the
mismatched byte gets compared to it.
0 1 2 3 4 5 6 7 8 9 10 11
a b c d e f g h i j k  l
    c ? e f

```