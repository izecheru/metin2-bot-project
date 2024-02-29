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
		test = Scanner::FindClass(OffsetSig("\x8B\x0D\x00\x00\x00\x00\x8D\x45\x00\x50\x8B\x45\x00\xFF\xB4\xC6", "xx????xx?xxx?xxx", 0x2));
		//pMetinStonePatch = Scanner::FindPattern(elaris::PatchMetinAutofarm.pattern, elaris::PatchMetinAutofarm.mask);
}