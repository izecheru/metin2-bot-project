#include "gameFunctions.h"
#include "scanner.h"

void GameFunc::Init() {
		UseSkill = Scanner::FindFunction<UseSkill_t>(elaris::SendUseSkill);
		DropItem = Scanner::FindFunction<SendItemDropPacket_t>(elaris::SendItemDropPacket);
		SetAutoAttackTarget = Scanner::FindFunction<SetAutoAttackTarget_t>(elaris::SetAutoAttackTarget);
		GetMainInstancePtr = Scanner::FindFunction<GetMainInstancePtr_t>(elaris::GetMainInstancePtr);
		CanUseSkill = Scanner::FindFunction<CanUseSkill_t>(elaris::CanUseSkill);
		SendPacket = Scanner::FindFunction<SendPacket_t>(elaris::SendPacket);
}