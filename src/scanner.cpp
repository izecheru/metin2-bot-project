#include "PatternScanner.h"

MODULEINFO PatternScanner::GetModuleInfo(char* szModule) {
		MODULEINFO modinfo = { 0 };
		HMODULE hModule = GetModuleHandleA(szModule);
		if (hModule == 0)
				return modinfo;
		GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
		return modinfo;
}

uintptr_t PatternScanner::FindPattern(const char* chPattern, const char* chMask) {
		MODULEINFO mInfo = GetModuleInfo(PatternScanner::chModule);
		DWORD size = (DWORD) mInfo.SizeOfImage;
		DWORD patternLength = (DWORD) strlen(chMask);
		dwBase = (DWORD) GetModuleHandleA(0);

		for (DWORD i = 0; i < size - patternLength; i++) {
				bool found = true;
				for (DWORD j = 0; j < patternLength; j++) {
						found &= chMask[j] == '?' || chPattern[j] == *(char*) (dwBase + i + j);
				}
				if (found) {
						return dwBase + i;
				}
		}
		return NULL;
}

uintptr_t PatternScanner::FindClass(OffsetSig signature) {
		uintptr_t addressFound = FindPattern(signature.pattern, signature.mask);
		uintptr_t result = *(uintptr_t*) (addressFound + signature.offset);
		return result;
}

uintptr_t PatternScanner::FindSignature(Sig sig) {
		return FindPattern(sig.pattern, sig.mask);
}