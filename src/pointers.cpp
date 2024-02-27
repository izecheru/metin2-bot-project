#include "pointers.h"
#include "signature.h"
#include "scanner.h"
void ptr::Init() {
		Scanner& scanner = Scanner::getInstance();
		ptr::CPythonCharacterManager = scanner.FindClass(elaris::CPyhtonCharacterManager);
		ptr::CPythonNetworkStream = scanner.FindClass(elaris::CPythonNetworkStream);
		ptr::CPythonPlayer = scanner.FindClass(elaris::CPythonPlayer);
		ptr::CFlyingManager = scanner.FindClass(elaris::CFlyingManager);
		ptr::CRaceManager = scanner.FindClass(elaris::CRaceManager);
		ptr::CPythonItem = scanner.FindClass(elaris::CPythonItem);
		ptr::CItemManager = scanner.FindClass(elaris::CItemManager);
}