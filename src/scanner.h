#pragma once
#include <Windows.h>
#include <Psapi.h>
#include "signature.h"
#include "singleton.h"

class Scanner : public Singleton<Scanner> {
public:
		inline static DWORD dwBase = 0;
		inline static char* chModule = (char*) "Elaris v1.0";
		static MODULEINFO GetModuleInfo(char* szModule);

		static uintptr_t FindPattern(const char* chPattern, const char* chMask);
		static uintptr_t FindClass(OffsetSig signature);
		static uintptr_t FindSignature(Sig sig);

		template<typename T>
		static T FindFunction(Sig sig) {
				uintptr_t address = FindSignature(sig);
				return reinterpret_cast<T>(address);
		}

		template<typename T>
		static T FindFunction(const char* pattern, const char* mask) {
				uintptr_t address = FindPattern(pattern, mask);
				return reinterpret_cast<T>(address);
		}
};

