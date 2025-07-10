#include "init.h"
#include "gameFunctions.h"
#include "gamePointers.h"
#include "hook.h"

void Init::InitHack()
{
  InitFuncs();
  InitPointers();
  InitHooks();
  InitGui();
}

void Init::InitFuncs() { GameFunction::Init(); }

void Init::InitHooks() { Hook::Init(); }

void Init::InitPointers() { GamePointers::Init(); }

void Init::InitGui() { UserInterface::getInstance()->init(); }