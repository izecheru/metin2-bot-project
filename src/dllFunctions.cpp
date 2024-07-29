#include "data.h"
#include "dllFunctions.h"
#include "hook.h"
#include "init.h"

DWORD WINAPI DllFunctions::ExitThread(LPVOID lpThreadParameter)
{
		Hook::Shutdown();
		FreeLibraryAndExitThread((HMODULE)(lpThreadParameter), TRUE);
		return TRUE;
}

DWORD WINAPI DllFunctions::MainThread(LPVOID lpThreadParameter)
{
		if (Data::g_hModule == NULL) 	Data::g_hModule = (HMODULE)lpThreadParameter;
		Init::InitHack();
		return TRUE;
}