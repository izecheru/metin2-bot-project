#include "dllFunctions.h"
#include "data.h"
#include "init.h"

DWORD WINAPI dllFunctions::ExitThread(LPVOID lpThreadParameter) {
		Hook::Shutdown();
		FreeLibraryAndExitThread((HMODULE) (lpThreadParameter), TRUE);
		return TRUE;
}

DWORD WINAPI dllFunctions::MainThread(LPVOID lpThreadParameter) {
		if (Data::g_hModule == NULL) 	Data::g_hModule = (HMODULE) lpThreadParameter;
		init::InitHack();
		return TRUE;
}