#pragma once
#include "signature.h"
#include "singleton.h"
#include <Psapi.h>
#include <string>
#include <vector>
#include <Windows.h>

namespace Scanner
{
		inline  DWORD dwBase = 0;
		inline  char* chModule = (char*) "Elaris v1.0";

		MODULEINFO GetModuleInfo(const char* szModule);

		uintptr_t FindPattern(const char* chPattern, const char* chMask);

		uintptr_t FindClass(const OffsetSig& signature);

		uintptr_t FindSignature(Sig sig);

		template<typename T>
		T FindFunction(Sig sig)
		{
				uintptr_t address = FindSignature(sig);
				return reinterpret_cast<T>(address);
		}

		template<typename T>
		T FindFunction(const char* pattern, const char* mask)
		{
				uintptr_t address = FindPattern(pattern, mask);
				return reinterpret_cast<T>(address);
		}
};

