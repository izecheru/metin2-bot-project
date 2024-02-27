#include "gameFunctions.h"
#include "scanner.h"

void GameFunc::Init() {
		Scanner& scanner = Scanner::getInstance();
		UseSkill = scanner.FindFunction<UseSkill_t>(elaris::SendUseSkill);
		DropItem = scanner.FindFunction<SendItemDropPacket_t>(elaris::SendItemDropPacket);
		SetAutoAttackTarget = scanner.FindFunction<SetAutoAttackTarget_t>(elaris::SetAutoAttackTarget);
		GetMainInstancePtr = scanner.FindFunction<GetMainInstancePtr_t>(elaris::GetMainInstancePtr);
		CanUseSkill = scanner.FindFunction<CanUseSkill_t>(elaris::CanUseSkill);
}