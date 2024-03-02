#pragma once
#include <Windows.h>

class Pointer {
public:
		static void Init();
		static inline uintptr_t CRaceManager = 0;
		static inline uintptr_t CFlyingManager = 0;
		static inline uintptr_t CPythonCharacterManager = 0;
		static inline uintptr_t CPythonNetworkStream = 0;
		static inline uintptr_t CPythonPlayer = 0;
		static inline uintptr_t CPythonItem = 0;
		static inline uintptr_t CInstanceBase = 0;
		static inline uintptr_t CItemManager = 0;
		static inline uintptr_t TCharacterInstanceMapAddress = 0;

		static inline uintptr_t pMetinStonePatch = 0;
		static inline uintptr_t oMetinStonePatch = 0;
};