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
using SendPacket_t = char(__fastcall*)(int, int, unsigned int, long** a3);

class GameFunc {
public:
		static void Init();
		inline static SendPacket_t SendPacket;
		inline static UseSkill_t UseSkill;
		inline static SendItemDropPacket_t DropItem;
		inline static SetAutoAttackTarget_t SetAutoAttackTarget;
		inline static GetMainInstancePtr_t GetMainInstancePtr;
		inline static CanUseSkill_t CanUseSkill;
};