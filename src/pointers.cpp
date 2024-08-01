#include "pointers.h"
#include "scanner.h"
#include "signature.h"

void Pointer::Init()
{
		CPythonCharacterManager = Scanner::FindClass(Elaris::CPyhtonCharacterManager);
		CPythonNetworkStream = Scanner::FindClass(Elaris::CPythonNetworkStream);
		CPythonPlayer = Scanner::FindClass(Elaris::CPythonPlayer);
		CFlyingManager = Scanner::FindClass(Elaris::CFlyingManager);
		CRaceManager = Scanner::FindClass(Elaris::CRaceManager);
		CPythonItem = Scanner::FindClass(Elaris::CPythonItem);
		CItemManager = Scanner::FindClass(Elaris::CItemManager);
		//		MetinStonePatch = Scanner::FindPattern(Elaris::PatchMetinAutofarm.pattern, Elaris::PatchMetinAutofarm.mask);
		SendShopSellPacket = Scanner::FindPattern((char*) Elaris::SendShopSellPacket.pattern, (char*) Elaris::SendShopSellPacket.mask);
}