#pragma once
#include <Windows.h>

// ui drawing
#include "gui.h"
#include <dinput.h>
#pragma comment(lib, "Dinput8.lib")
#pragma comment(lib, "Dxguid.lib")

using WndProc_t = LRESULT(CALLBACK*)(HWND, UINT, WPARAM, LPARAM);
using GetDeviceState_t = HRESULT(__stdcall*)(IDirectInputDevice8* pThis, DWORD cbData, LPVOID lpvData);
using GetDeviceData_t = HRESULT(__stdcall*)(IDirectInputDevice8*, DWORD, LPDIDEVICEOBJECTDATA, LPDWORD, DWORD);

// game function type
using UseSkill_t = bool(__thiscall*)(void*, int index, int target);

namespace Hook {
		inline HWND window;
		inline void** deviceTable;
		inline void** inputDeviceTable;
		inline WndProc_t oWndProc;
		inline HMODULE g_hModule;
		inline GetDeviceState_t pGetDeviceState;
		HRESULT __stdcall GetDeviceState(IDirectInputDevice8* pThis, DWORD cbData, LPVOID lpvData);
		inline GetDeviceData_t pGetDeviceData;
		HRESULT __stdcall GetDeviceData(IDirectInputDevice8* pThis, DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags);

		inline UseSkill_t UseSkill = nullptr;


		bool Setup();
		bool Shutdown();
		bool GetD3D9Device();
		bool GetD3D9InputDevice();
		LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};