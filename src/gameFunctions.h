#pragma once
#include "entity.h"
#include "singleton.h"
#include <vector>
#include <Windows.h>

using UseSkill_t = bool(__thiscall*)(void*, int index, int target);
using SendItemDropPacket_t = bool(__thiscall*)(void*, int index, int quantity);
using SetAutoAttackTarget_t = int(__thiscall*)(void*, int targetVID);
using GetMainInstancePtr_t = Entity * (__thiscall*)(void*);
using CanUseSkill_t = bool(__thiscall*)(void*);
using RecvPacket_t = char(__fastcall*)(int pThis, int ebx, unsigned int size, long** buffer);
using SendPacket_t = char(__thiscall*)(void* pthis, unsigned int size, std::vector<BYTE> buffer);
using SendItemUsePacket_t = char(__thiscall*)(void* pCNetwork, int itemPos);

class GameFunction
{
public:
		static void Init();
		inline static SendItemUsePacket_t pSendItemUsePacket;
		inline static SendPacket_t SendPacket;
		inline static RecvPacket_t RecvPacket;
		inline static UseSkill_t UseSkill;
		inline static SendItemDropPacket_t DropItem;
		inline static SetAutoAttackTarget_t SetAutoAttackTarget;
		inline static GetMainInstancePtr_t GetMainInstancePtr;
		inline static CanUseSkill_t CanUseSkill;

		static void SendItemUsePacket(int itemPos);
};