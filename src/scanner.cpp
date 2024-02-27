#include "scanner.h"

MODULEINFO Scanner::GetModuleInfo(char* szModule) {
		MODULEINFO modinfo = { 0 };
		HMODULE hModule = GetModuleHandleA(szModule);
		if (hModule == 0)
				return modinfo;
		GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
		return modinfo;
}

uintptr_t Scanner::FindPattern(const char* chPattern, const char* chMask) {
		MODULEINFO mInfo = GetModuleInfo(Scanner::chModule);
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

uintptr_t Scanner::FindClass(OffsetSig signature) {
		uintptr_t addressFound = FindPattern(signature.pattern, signature.mask);
		uintptr_t result = (addressFound + signature.offset);
		return *(uintptr_t*) result;
}

uintptr_t Scanner::FindSignature(Sig sig) {
		return FindPattern(sig.pattern, sig.mask);
}