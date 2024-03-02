#include "pointers.h"
#include "signature.h"
#include "scanner.h"
void Pointer::Init() {
		CPythonCharacterManager = Scanner::FindClass(elaris::CPyhtonCharacterManager);
		CPythonNetworkStream = Scanner::FindClass(elaris::CPythonNetworkStream);
		CPythonPlayer = Scanner::FindClass(elaris::CPythonPlayer);
		CFlyingManager = Scanner::FindClass(elaris::CFlyingManager);
		CRaceManager = Scanner::FindClass(elaris::CRaceManager);
		CPythonItem = Scanner::FindClass(elaris::CPythonItem);
		CItemManager = Scanner::FindClass(elaris::CItemManager);
		//pMetinStonePatch = Scanner::FindPattern(elaris::PatchMetinAutofarm.pattern, elaris::PatchMetinAutofarm.mask);
}