#include "init.h"

void init::InitHack() {
		InitFuncs();
		InitPointers();
		InitHooks();
}

void init::InitFuncs() {
		GameFunc& gFunc = GameFunc::getInstance();
		gFunc.Init();
}

void init::InitHooks() {
		Hook::Init();
}

void init::InitPointers() {
		ptr::Init();
}