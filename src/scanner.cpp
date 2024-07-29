#include "scanner.h"

MODULEINFO Scanner::GetModuleInfo(char* szModule)
{
		MODULEINFO modinfo = { 0 };
		HMODULE hModule = GetModuleHandleA(szModule);
		if (hModule == 0)
				return modinfo;
		GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
		return modinfo;
}

uintptr_t Scanner::FindPattern(const char* chPattern, const char* chMask)
{
		dwBase = (DWORD)GetModuleHandleA(0);
		chModule = (char*)"Elaris v1.0";
		MODULEINFO mInfo = GetModuleInfo(Scanner::chModule);
		DWORD size = (DWORD)mInfo.SizeOfImage;
		DWORD patternLength = (DWORD)strlen(chMask);

		for (DWORD i = 0; i < size - patternLength; i++)
		{
				bool found = true;
				for (DWORD j = 0; j < patternLength; j++)
				{
						found &= chMask[j] == '?' || chPattern[j] == *(char*)(dwBase + i + j);
				}
				if (found)
				{
						return dwBase + i;
				}
		}
		return NULL;
}

uintptr_t Scanner::FindClass(OffsetSig signature)
{
		uintptr_t addressFound = FindPattern(signature.pattern, signature.mask);
		uintptr_t result = (addressFound + signature.offset);
		return *(uintptr_t*)result;
}

uintptr_t Scanner::FindSignature(Sig sig)
{
		return FindPattern(sig.pattern, sig.mask);
}

uintptr_t Scanner::FindIdaPattern(char* signature)
{
		static auto pattern_to_byte = [](const char* pattern)
				{
						auto bytes = std::vector<char>{};
						auto start = const_cast<char*>(pattern);
						auto end = const_cast<char*>(pattern) + strlen(pattern);

						for (auto current = start; current < end; ++current)
						{
								if (*current == '?')
								{
										++current;
										if (*current == '?')
												++current;
										bytes.push_back('\?');
								}
								else
								{
										bytes.push_back(strtoul(current, &current, 16));
								}
						}
						return bytes;
				};

		dwBase = (DWORD)GetModuleHandleA(0);
		chModule = (char*)"Elaris v1.0";
		MODULEINFO mInfo = GetModuleInfo(Scanner::chModule);
		DWORD size = (DWORD)mInfo.SizeOfImage;

		auto patternBytes = pattern_to_byte(signature);

		DWORD64 patternLength = patternBytes.size();
		auto data = patternBytes.data();

		for (DWORD64 i = 0; i < size - patternLength; i++)
		{
				bool found = true;
				for (DWORD64 j = 0; j < patternLength; j++)
				{
						char a = '\?';
						char b = *(char*)(dwBase + i + j);
						found &= data[j] == a || data[j] == b;
				}
				if (found)
				{
						return dwBase + i;
				}
		}
		return NULL;
}
