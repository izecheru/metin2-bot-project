#pragma once
#include <Windows.h>

namespace DllFunctions
{
		DWORD WINAPI ExitThread(LPVOID lpThreadParameter);

		DWORD WINAPI MainThread(LPVOID lpThreadParameter);
};
