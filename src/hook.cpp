#include "pointers.h"
#include "scanner.h"
#include "hook.h"
#include "data.h"

bool Hook::Setup() {
		// all the magic happens here
		if (GetD3D9Device() && GetD3D9InputDevice()) {
				Data::window = FindWindowA(NULL, "Elaris v1.0");
				oWndProc = (WndProc_t) SetWindowLongPtr(Data::window, GWL_WNDPROC, (LONG_PTR) Hook::WndProc);
				Gui::pEndScene = (EndScene_t) deviceTable[42];
				Gui::pReset = (Reset_t) deviceTable[16];
				pGetDeviceData = (GetDeviceData_t) inputDeviceTable[10];
				pGetDeviceState = (GetDeviceState_t) inputDeviceTable[9];
				// get the game pointers
				UseSkill = (UseSkill_t) PatternScanner::FindSignature(elaris::SendUseSkill);
				Pointers::UseSkillAddress = (uintptr_t) UseSkill;
				Pointers::ptrCPythonNetworkStream = PatternScanner::FindClass(elaris::CPythonNetworkStream);
				// hook functions
				DetourTransactionBegin();
				DetourUpdateThread(GetCurrentThread());
				DetourAttach(&(PVOID&) Gui::pEndScene, Gui::EndScene);
				DetourAttach(&(PVOID&) Gui::pReset, Gui::Reset);
				DetourAttach(&(PVOID&) pGetDeviceData, GetDeviceData);
				DetourAttach(&(PVOID&) pGetDeviceState, GetDeviceState);
				DetourTransactionCommit();
				return true;
		}
		return false;
}

bool Hook::Shutdown() {
		if (Gui::InitImGui) {
				ImGui_ImplDX9_Shutdown();
				ImGui_ImplWin32_Shutdown();
				ImGui::DestroyContext();
		}
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&) Gui::pEndScene, Gui::EndScene);
		DetourDetach(&(PVOID&) Gui::pReset, Gui::Reset);
		DetourDetach(&(PVOID&) pGetDeviceData, GetDeviceData);
		DetourDetach(&(PVOID&) pGetDeviceState, GetDeviceState);
		DetourTransactionCommit();
		SetWindowLongPtr(Data::window, GWLP_WNDPROC, (LONG_PTR) oWndProc);
		return true;
}

bool Hook::GetD3D9InputDevice() {
		IDirectInput8* pDirectInput = nullptr;
		if (DirectInput8Create(Data::g_hModule, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*) &pDirectInput, NULL) != DI_OK) {
				return false;
		}
		LPDIRECTINPUTDEVICE8 lpdiMouse;
		if (pDirectInput->CreateDevice(GUID_SysMouse, &lpdiMouse, NULL) != DI_OK) {
				pDirectInput->Release();
				return false;
		}
		inputDeviceTable = *reinterpret_cast<void***>(lpdiMouse);
		pDirectInput->Release();
		lpdiMouse->Release();
		return true;
}

bool Hook::GetD3D9Device() {
		IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION); // create IDirect3D9 object
		if (!pD3D) {
				return false;
		}

		HWND tmpWnd = CreateWindowA("BUTTON", "Temp Window", WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, NULL, NULL, Data::g_hModule, NULL);
		if (tmpWnd == NULL) {
				return false;
		}
		D3DPRESENT_PARAMETERS d3dpp = { 0 };
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = tmpWnd;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		IDirect3DDevice9* pDevice = nullptr;
		HRESULT result = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, tmpWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDevice);
		if (FAILED(result) || !pDevice) {
				pD3D->Release();
				DestroyWindow(tmpWnd);
				return false;
		}
		deviceTable = *reinterpret_cast<void***>(pDevice);
		pDevice->Release();
		pD3D->Release();
		DestroyWindow(tmpWnd);
		return true;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg,
		WPARAM wParam, LPARAM lParam);
LRESULT WINAPI  Hook::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		if (Gui::showMenu) {
				ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

				if (uMsg == WM_KEYDOWN) {
						switch (wParam) {
								case VK_INSERT:
										Gui::showMenu = !Gui::showMenu;
										break;
								case VK_END:
										Gui::toDetach = !Gui::toDetach;
										break;
						}
				}
				return TRUE;
		}
		if (uMsg == WM_KEYDOWN) {
				switch (wParam) {
						case VK_INSERT:
								Gui::showMenu = !Gui::showMenu;
								break;
				}
		}
		return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall Hook::GetDeviceState(IDirectInputDevice8* pThis, DWORD cbData, LPVOID lpvData) {
		HRESULT result = pGetDeviceState(pThis, cbData, lpvData);
		if (result == DI_OK) {
				if (Gui::showMenu) {
						((LPDIMOUSESTATE2) lpvData)->rgbButtons[0] = 0;
						((LPDIMOUSESTATE2) lpvData)->rgbButtons[1] = 0;
				}
		}
		return result;
}

HRESULT __stdcall Hook::GetDeviceData(IDirectInputDevice8* pThis, DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags) {
		HRESULT result = pGetDeviceData(pThis, cbObjectData, rgdod, pdwInOut, dwFlags);
		if (result == DI_OK) {
				if (Gui::showMenu) {
						*pdwInOut = 0; //set array size 0
				}
		}
		return result;
}