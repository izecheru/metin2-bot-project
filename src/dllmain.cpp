#include "dllFunctions.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
		switch (dwReason) {
				case DLL_PROCESS_ATTACH:
						DisableThreadLibraryCalls(hModule);
						CreateThread(nullptr, 0, dllFunctions::MainThread, hModule, 0, nullptr);
						break;
				case DLL_PROCESS_DETACH:
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