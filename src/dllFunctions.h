#pragma once
#include <Windows.h>

class DllFunctions
{
public:
		static DWORD WINAPI ExitThread(LPVOID lpThreadParameter);
		static DWORD WINAPI MainThread(LPVOID lpThreadParameter);
};
