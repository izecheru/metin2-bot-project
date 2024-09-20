#pragma once
#include "entity.h"
#include <Windows.h>
#include <map>

namespace GamePointers {
void Init();

// Those are all game class pointers that we must use to call __thiscall
// functions
inline uintptr_t CRaceManager = 0;
inline uintptr_t CFlyingManager = 0;
inline uintptr_t CPythonCharacterManager = 0;
inline uintptr_t CPythonNetworkStream = 0;
inline uintptr_t CPythonPlayer = 0;
inline uintptr_t CPythonItem = 0;
inline uintptr_t CInstanceBase = 0;
inline uintptr_t CItemManager = 0;
inline uintptr_t CPythonBackground = 0;
inline uintptr_t CPythonMiniMap = 0;

using TCharacterInstanceMap = std::map<DWORD, Entity::Mob *>;
inline TCharacterInstanceMap kaliveInstanceMap;

inline uintptr_t testPtr = 0;
inline uintptr_t *testPtrr = 0;
}; // namespace GamePointers
