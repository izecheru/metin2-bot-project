#include "classPointers.h"
#include "scanner.h"
#include "signature.h"

void ClassPointers::Init() {
	CPythonCharacterManager = Scanner::FindClass(Elaris::CPyhtonCharacterManager);
	CPythonNetworkStream = Scanner::FindClass(Elaris::CPythonNetworkStream);
	CPythonBackground = Scanner::FindClass(Elaris::CPyhtonBackground);
	CFlyingManager = Scanner::FindClass(Elaris::CFlyingManager);
	CPythonMiniMap = Scanner::FindClass(Elaris::CPyhtonMiniMap);
	CPythonPlayer = Scanner::FindClass(Elaris::CPythonPlayer);
	CRaceManager = Scanner::FindClass(Elaris::CRaceManager);
	CItemManager = Scanner::FindClass(Elaris::CItemManager);
	CPythonItem = Scanner::FindClass(Elaris::CPythonItem);
	CInstanceBase = Scanner::FindClass(Elaris::CInstanceBase);
}
