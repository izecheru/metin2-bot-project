#include "pointers.h"
#include "signature.h"
#include "scanner.h"

void Pointer::Init() {
		CPythonCharacterManager = Scanner::FindClass(elaris::CPyhtonCharacterManager);
		CPythonNetworkStream = Scanner::FindClass(elaris::CPythonNetworkStream);
		CPythonBackground = Scanner::FindClass(elaris::CPyhtonBackground);
		CFlyingManager = Scanner::FindClass(elaris::CFlyingManager);
		CPythonMiniMap = Scanner::FindClass(elaris::CPyhtonMiniMap);
		CPythonPlayer = Scanner::FindClass(elaris::CPythonPlayer);
		CRaceManager = Scanner::FindClass(elaris::CRaceManager);
		CItemManager = Scanner::FindClass(elaris::CItemManager);
		CPythonItem = Scanner::FindClass(elaris::CPythonItem);
}