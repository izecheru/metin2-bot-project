#pragma once
#include <Windows.h>

#include "dllFunctions.h"
#include "data.h"
#include "patch.h"
#include "gui.h"
#include "../ext/detours/detours.h"
// ui drawing
#include <dinput.h>
#pragma comment(lib, "Dinput8.lib")
#pragma comment(lib, "Dxguid.lib")

using WndProc_t = LRESULT(CALLBACK*)(HWND, UINT, WPARAM, LPARAM);
using GetDeviceState_t = HRESULT(__stdcall*)(IDirectInputDevice8* pThis, DWORD cbData, LPVOID lpvData);
using GetDeviceData_t = HRESULT(__stdcall*)(IDirectInputDevice8*, DWORD, LPDIDEVICEOBJECTDATA, LPDWORD, DWORD);
using EndScene_t = HRESULT(__stdcall*)(IDirect3DDevice9* pDevice);
using Reset_t = HRESULT(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);

class Hook {
private:
		static inline FILE* fp = nullptr;
		static inline void** deviceTable;
		static inline void** inputDeviceTable;

public:
		// just for packet send reading
		static char __fastcall hkSendPacket(int a1, int ebx, unsigned int a2, long** a3);

		// gui related hooks
		static inline EndScene_t pEndScene = nullptr;
		static inline EndScene_t oEndScene = nullptr;

		static inline Reset_t pReset = nullptr;
		static inline Reset_t oReset = nullptr;

		static inline WndProc_t oWndProc;

		static inline GetDeviceState_t pGetDeviceState = nullptr;
		static inline GetDeviceState_t oGetDeviceState = nullptr;

		static inline GetDeviceData_t pGetDeviceData = nullptr;
		static inline GetDeviceData_t oGetDeviceData = nullptr;

		static HRESULT __stdcall EndScene(IDirect3DDevice9* pDevice);
		static HRESULT __stdcall Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* params);
		static HRESULT __stdcall GetDeviceState(IDirectInputDevice8* pThis, DWORD cbData, LPVOID lpvData);
		static HRESULT __stdcall GetDeviceData(IDirectInputDevice8* pThis, DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags);

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		static bool Init();
		static bool Shutdown();

		static bool InitMinHook();
		static bool GetD3D9Device();
		static bool GetD3D9InputDevice();
};