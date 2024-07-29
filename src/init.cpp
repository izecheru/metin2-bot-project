#include "classPointers.h"
#include "gameFunctions.h"
#include "hook.h"
#include "init.h"

void Init::InitHack()
{
		InitFuncs();
		InitPointers();
		InitHooks();
		InitGui();
}

void Init::InitFuncs()
{
		GameFunction::Init();
}

void Init::InitHooks()
{
		Hook::Init();
}

void Init::InitPointers()
{
		ClassPointers::Init();
}

void Init::InitGui()
{
		Gui::Init();
}