#pragma once
#include "entity.h"
#include <vector>
#include <Windows.h>

using SendItemDropPacket_t = bool(__thiscall*)(void*, int index, int quantity);
using SetAutoAttackTarget_t = int(__thiscall*)(void*, int targetVID);
using GetMainInstancePtr_t = Entity * (__thiscall*)(void*);
using CanUseSkill_t = bool(__thiscall*)(void*);
using RecvPacket_t = char(__fastcall*)(int pThis, int ebx, unsigned int size, long** buffer);
using SendPacket_t = char(__thiscall*)(void* pthis, unsigned int size, std::vector<BYTE> buffer);

// those functions work
using UseSkill_t = bool(__thiscall*)(void*, int index, int target);
using SendItemUsePacket_t = char(__thiscall*)(void* pCNetwork, int itemPos);
using SendShopSellPacket_t = char(__thiscall*)(void* pCNetwork, char slot);

namespace GameFunction
{
		/// Initialize the function pointers
		void Init();

		inline  SendItemUsePacket_t pSendItemUsePacket;
		inline  SendShopSellPacket_t pSendShopSellPacket;


		inline  SendPacket_t SendPacket;
		inline  RecvPacket_t RecvPacket;
		inline  UseSkill_t UseSkill;
		inline  SendItemDropPacket_t DropItem;
		inline  SetAutoAttackTarget_t SetAutoAttackTarget;
		inline  GetMainInstancePtr_t GetMainInstancePtr;
		inline  CanUseSkill_t CanUseSkill;

		void SendItemUsePacket(int itemPos);
		void SendShopSellPacket(char itemPos);
};
