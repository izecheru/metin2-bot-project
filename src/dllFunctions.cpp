#include "dllFunctions.h"
#include "data.h"
#include "hook.h"
#include "init.h"

DWORD WINAPI DllFunctions::ExitThread(const LPVOID lpThreadParameter)
{
		Hook::Shutdown();
		FreeLibraryAndExitThread(HMODULE(lpThreadParameter), TRUE);
		return TRUE;
}

DWORD WINAPI DllFunctions::MainThread(const LPVOID lpThreadParameter)
{
		if (Data::g_hModule == nullptr)
				Data::g_hModule = HMODULE(lpThreadParameter);
		Init::InitHack();
		return TRUE;
}