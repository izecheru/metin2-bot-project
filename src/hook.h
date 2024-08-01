#pragma once
#include <Windows.h>

#include "../ext/detours/detours.h"
#include "../ext/directx/Include/d3d9.h"
#include "../ext/directx/Include/dinput.h"
#include "data.h"
#include "dllFunctions.h"
#include "gui.h"

using WndProc_t = LRESULT(CALLBACK*)(HWND, UINT, WPARAM, LPARAM);
using GetDeviceState_t = HRESULT(__stdcall*)(IDirectInputDevice8* pThis, DWORD cbData, LPVOID lpvData);
using GetDeviceData_t = HRESULT(__stdcall*)(IDirectInputDevice8*, DWORD, LPDIDEVICEOBJECTDATA, LPDWORD, DWORD);
using EndScene_t = HRESULT(__stdcall*)(IDirect3DDevice9* pDevice);
using Reset_t = HRESULT(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
using ToHookSendPacket_t = char(__fastcall*)(int, int, unsigned int, long** a3);

namespace Hook
{
		inline void** deviceTable;
		inline void** inputDeviceTable;

		inline ToHookSendPacket_t pSendPacket = nullptr;
		inline ToHookSendPacket_t oSendPacket = nullptr;


		inline char __fastcall hkSendPacket(int pThis, int ebx, unsigned int a2, long** a3);

		// gui related hooks
		inline EndScene_t pEndScene = nullptr;

		inline Reset_t pReset = nullptr;

		inline WndProc_t oWndProc;

		inline GetDeviceState_t pGetDeviceState = nullptr;

		inline GetDeviceData_t pGetDeviceData = nullptr;

		HRESULT __stdcall EndScene(IDirect3DDevice9* pDevice);

		HRESULT __stdcall Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* params);

		HRESULT __stdcall GetDeviceState(IDirectInputDevice8* pThis, DWORD cbData, LPVOID lpvData);

		HRESULT __stdcall GetDeviceData(IDirectInputDevice8* pThis, DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod,
																		LPDWORD pdwInOut, DWORD dwFlags);

		LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		bool Init();

		bool Shutdown();

		bool GetD3D9Device();

		bool GetD3D9InputDevice();
};
