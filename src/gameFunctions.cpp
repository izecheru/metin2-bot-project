#include "gameFunctions.h"
#include "scanner.h"
#include "pointers.h"

void GameFunc::Init() {
		UseSkill = Scanner::FindFunction<UseSkill_t>(elaris::SendUseSkill);
		DropItem = Scanner::FindFunction<SendItemDropPacket_t>(elaris::SendItemDropPacket);
		SetAutoAttackTarget = Scanner::FindFunction<SetAutoAttackTarget_t>(elaris::SetAutoAttackTarget);
		GetMainInstancePtr = Scanner::FindFunction<GetMainInstancePtr_t>(elaris::GetMainInstancePtr);
		CanUseSkill = Scanner::FindFunction<CanUseSkill_t>(elaris::CanUseSkill);
		SendPacket = Scanner::FindFunction<SendPacket_t>(elaris::SendPacket);
}

TCharacterInstanceMap* GameFunc::GetEntities() {
		// Assuming Pointer::CPythonCharacterManager is the base address of CPythonCharacterManager structure
		DWORD* characterManagerPtr = *reinterpret_cast<DWORD**>(Pointer::CPythonCharacterManager);

		// Assuming CInstanceBase is at offset 0xC from CPythonCharacterManager
		DWORD* instanceBasePtr = reinterpret_cast<DWORD*>(characterManagerPtr + 0x14);

		// Assuming TCharacterInstanceMap is at offset 0x8 from CInstanceBase
		TCharacterInstanceMap* entitiesMap = reinterpret_cast<TCharacterInstanceMap*>(instanceBasePtr + 0x8);

		return entitiesMap;
}