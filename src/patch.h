#pragma once
#include <Windows.h>
#include "cheatVars.h"
#include "pointers.h"

using Patch_t = void(__stdcall*)();

class Patch {
public:
		static int MetinAutoFarmPatch(int* address);
};