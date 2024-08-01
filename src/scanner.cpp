#include "scanner.h"

MODULEINFO Scanner::GetModuleInfo(const char* szModule)
{
		MODULEINFO modinfo = { nullptr };
		const HMODULE hModule = GetModuleHandleA(szModule);
		if (hModule == nullptr)
				return modinfo;
		GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
		return modinfo;
}

uintptr_t Scanner::FindPattern(const char* chPattern, const char* chMask)
{
		dwBase = reinterpret_cast<DWORD>(GetModuleHandleA(0));
		chModule = (char*) "Elaris v1.0";
		const MODULEINFO mInfo = GetModuleInfo(Scanner::chModule);
		const DWORD size = (DWORD) mInfo.SizeOfImage;
		const DWORD patternLength = (DWORD) strlen(chMask);

		for (DWORD i = 0; i < size - patternLength; i++)
		{
				bool found = true;
				for (DWORD j = 0; j < patternLength; j++)
				{
						found &= chMask[j] == '?' || chPattern[j] == *reinterpret_cast<char*>(dwBase + i + j);
				}
				if (found)
				{
						return dwBase + i;
				}
		}
		return NULL;
}

uintptr_t Scanner::FindClass(const OffsetSig& signature)
{
		const uintptr_t addressFound = FindPattern(signature.pattern, signature.mask);
		const uintptr_t result = (addressFound + signature.offset);
		return *reinterpret_cast<uintptr_t*>(result);
}

uintptr_t Scanner::FindSignature(const Sig sig)
{
		return FindPattern(sig.pattern, sig.mask);
}
