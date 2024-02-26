#pragma once
#include <Windows.h>

#include "dllFunctions.h"
#include "gui.h"
// ui drawing
#include <dinput.h>
#pragma comment(lib, "Dinput8.lib")
#pragma comment(lib, "Dxguid.lib")

using WndProc_t = LRESULT(CALLBACK*)(HWND, UINT, WPARAM, LPARAM);
using GetDeviceState_t = HRESULT(__stdcall*)(IDirectInputDevice8* pThis, DWORD cbData, LPVOID lpvData);
using GetDeviceData_t = HRESULT(__stdcall*)(IDirectInputDevice8*, DWORD, LPDIDEVICEOBJECTDATA, LPDWORD, DWORD);
using EndScene_t = HRESULT(__stdcall*)(IDirect3DDevice9* pDevice);
using Reset_t = HRESULT(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);

// game function type
using UseSkill_t = bool(__thiscall*)(void*, int index, int target);
using SendItemDropPacket_t = bool(__thiscall*)(void*, int index, int quantity);

namespace Hook {
		inline Gui& gui = Gui::getInstance();
		inline void** deviceTable;
		inline void** inputDeviceTable;
		inline EndScene_t pEndScene = nullptr;
		inline Reset_t pReset = nullptr;
		inline WndProc_t oWndProc;
		inline GetDeviceState_t pGetDeviceState;
		inline GetDeviceData_t pGetDeviceData;
		inline UseSkill_t UseSkill = nullptr;
		inline SendItemDropPacket_t DropItem = nullptr;

		HRESULT __stdcall EndScene(IDirect3DDevice9* pDevice);
		HRESULT __stdcall Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* params);
		HRESULT __stdcall GetDeviceState(IDirectInputDevice8* pThis, DWORD cbData, LPVOID lpvData);
		HRESULT __stdcall GetDeviceData(IDirectInputDevice8* pThis, DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags);

		bool Setup();
		bool Shutdown();
		bool GetD3D9Device();
		bool GetD3D9InputDevice();
		LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};