#pragma once
#include <Windows.h>
#include <Psapi.h>
#include "signature.h"
#include "singleton.h"

class Scanner : public Singleton<Scanner> {
public:
		DWORD dwBase = NULL;
		char* chModule = (char*) "Elaris v1.0";
		MODULEINFO GetModuleInfo(char* szModule);

		uintptr_t FindPattern(const char* chPattern, const char* chMask);
		uintptr_t FindClass(OffsetSig signature);
		uintptr_t FindSignature(Sig sig);

		template<typename T>
		T FindFunction(Sig sig) {
				uintptr_t address = FindSignature(sig);
				return reinterpret_cast<T>(address);
		}

		template<typename T>
		T FindFunction(const char* pattern, const char* mask) {
				uintptr_t address = FindPattern(pattern, mask);
				return reinterpret_cast<T>(address);
		}
};

