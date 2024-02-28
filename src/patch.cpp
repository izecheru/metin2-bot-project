#include "patch.h"
#include "cheatVars.h"

int Patch::MetinAutoFarmPatch(int* address) {
		*address = Var::metinLimit;
		return Pointer::pMetinStonePatch;
}