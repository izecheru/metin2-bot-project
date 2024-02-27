#pragma once
#include <Windows.h>
#include "singleton.h"
#include "entity.h"
// game function type
using UseSkill_t = bool(__thiscall*)(void*, int index, int target);
using SendItemDropPacket_t = bool(__thiscall*)(void*, int index, int quantity);
using SetAutoAttackTarget_t = int(__thiscall*)(void*, int targetVID);
using GetMainInstancePtr_t = Entity * (__thiscall*)(void*);
using CanUseSkill_t = bool(__thiscall*)(void*);
using RecvPacket_t = char(__thiscall*)(void* pThis, int Size, char* pDestBuffer);

class GameFunc : public Singleton<GameFunc> {
public:
		void Init();
		UseSkill_t UseSkill = nullptr;
		SendItemDropPacket_t DropItem = nullptr;
		SetAutoAttackTarget_t SetAutoAttackTarget = nullptr;
		GetMainInstancePtr_t GetMainInstancePtr = nullptr;
		CanUseSkill_t CanUseSkill = nullptr;
};