#pragma once
#include <Windows.h>

namespace dllFunctions {
		DWORD WINAPI ExitThread(LPVOID lpThreadParameter);
		DWORD WINAPI MainThread(LPVOID lpThreadParameter);
}
