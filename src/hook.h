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
using SendUseItemPacket_t = char(__thiscall*)(void*, uint16_t);

class Hook
{
private:
		static inline void** deviceTable;
		static inline void** inputDeviceTable;

public:
		static inline ToHookSendPacket_t pSendPacket = nullptr;
		static inline ToHookSendPacket_t oSendPacket = nullptr;

		static inline SendUseItemPacket_t pSendUseItemPacket = nullptr;
		static inline char __fastcall hkSendPacket(int pThis, int ebx, unsigned int a2, long** a3);
		static inline char __stdcall hkSendUseItemPacket(void* pThis, uint16_t  itemPos);

		// gui related hooks
		static inline EndScene_t pEndScene = nullptr;

		static inline Reset_t pReset = nullptr;

		static inline WndProc_t oWndProc;

		static inline GetDeviceState_t pGetDeviceState = nullptr;

		static inline GetDeviceData_t pGetDeviceData = nullptr;

		static HRESULT __stdcall EndScene(IDirect3DDevice9* pDevice);
		static HRESULT __stdcall Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* params);
		static HRESULT __stdcall GetDeviceState(IDirectInputDevice8* pThis, DWORD cbData, LPVOID lpvData);
		static HRESULT __stdcall GetDeviceData(IDirectInputDevice8* pThis, DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags);

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		static bool Init();
		static bool Shutdown();

		static bool GetD3D9Device();
		static bool GetD3D9InputDevice();
};