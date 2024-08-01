#pragma once
#include <Windows.h>

class ClassPointers {
public:
	static void Init();

	// Those are all game class pointers that we must use to call __thiscall functions
	static inline uintptr_t CRaceManager = 0;
	static inline uintptr_t CFlyingManager = 0;
	static inline uintptr_t CPythonCharacterManager = 0;
	static inline uintptr_t CPythonNetworkStream = 0;
	static inline uintptr_t CPythonPlayer = 0;
	static inline uintptr_t CPythonItem = 0;
	static inline uintptr_t CInstanceBase = 0;
	static inline uintptr_t CItemManager = 0;
	static inline uintptr_t CPythonBackground = 0;
	static inline uintptr_t CPythonMiniMap = 0;
};
