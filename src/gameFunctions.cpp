#include "classPointers.h"
#include "gameFunctions.h"
#include "scanner.h"

void GameFunction::Init()
{
		UseSkill = Scanner::FindFunction<UseSkill_t>(Elaris::SendUseSkill);
		DropItem = Scanner::FindFunction<SendItemDropPacket_t>(Elaris::SendItemDropPacket);
		SetAutoAttackTarget = Scanner::FindFunction<SetAutoAttackTarget_t>(Elaris::SetAutoAttackTarget);
		GetMainInstancePtr = Scanner::FindFunction<GetMainInstancePtr_t>(Elaris::GetMainInstancePtr);
		CanUseSkill = Scanner::FindFunction<CanUseSkill_t>(Elaris::CanUseSkill);
		SendPacket = Scanner::FindFunction<SendPacket_t>(Elaris::SendPacket);
		pSendItemUsePacket = Scanner::FindFunction<SendItemUsePacket_t>(Elaris::SendItemUsePacket);
		pSendShopSellPacket = Scanner::FindFunction<SendShopSellPacket_t>(Elaris::SendShopSellPacket);
		//RecvPacket = Scanner::FindFunction<RecvPacket_t>(Elaris::RecvPacket);
}

void GameFunction::SendItemUsePacket(int itemPos)
{
		// first is 1
		// second is 257
		// third is 513
		// so A of n is 1 + ( n - 1) * 256
		int element = 1 + (itemPos - 1) * 256;
		pSendItemUsePacket(*(void**) ClassPointers::CPythonNetworkStream, element);
}

void GameFunction::SendShopSellPacket(char itemPos)
{
		pSendShopSellPacket(*(void**) ClassPointers::CPythonNetworkStream, itemPos);
}
