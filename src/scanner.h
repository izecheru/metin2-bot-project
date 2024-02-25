#pragma once
#include <Windows.h>
#include <Psapi.h>

#include "GameSignatures.h"

namespace PatternScanner {
		inline DWORD dwBase = NULL;
		inline char* chModule = (char*) "Elaris v1.0";
		MODULEINFO GetModuleInfo(char* szModule);

		uintptr_t FindPattern(const char* chPattern, const char* chMask);
		uintptr_t FindClass(OffsetSig signature);
		uintptr_t FindSignature(Sig sig);
};
