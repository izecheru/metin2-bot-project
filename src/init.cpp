#include "init.h"
void init::InitHack() {
		InitFuncs();
		InitPointers();
		InitHooks();
		InitGui();
}

void init::InitFuncs() {
		GameFunc::Init();
}

void init::InitHooks() {
		Hook::Init();
}

void init::InitPointers() {
		Pointer::Init();
}

void init::InitGui() {
		Gui::Init();
}