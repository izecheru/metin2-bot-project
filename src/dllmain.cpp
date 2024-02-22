#include "hook.h"

DWORD WINAPI ExitThread(LPVOID lpThreadParameter) {
		FreeLibraryAndExitThread((HMODULE) (lpThreadParameter), TRUE);
		return TRUE;
}

DWORD WINAPI MainThread(LPVOID lpThreadParameter) {
		if (Hook::g_hModule == NULL) Hook::g_hModule = (HMODULE) lpThreadParameter;
		Hook::Setup();
		return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
		switch (dwReason) {
				case DLL_PROCESS_ATTACH:
						DisableThreadLibraryCalls(hModule);
						CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
						break;
				case DLL_PROCESS_DETACH:
						CreateThread(nullptr, 0, ExitThread, hModule, 0, nullptr);
						break;
				case DLL_THREAD_ATTACH:
						break;
				case DLL_THREAD_DETACH:
						break;
				default:
						break;
		}
		return TRUE;
}