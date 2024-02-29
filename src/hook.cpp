#include "hook.h"


#define CONSOLE1
#ifdef CONSOLE
#include<iostream>


void console(LPVOID hModule) { //console assignment

		if (AllocConsole()) {
				freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout); //have to use freopen_s instead of freopen to get ride of the _CRT_SECURE_NO_WARNINGS message
				freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
				freopen_s(reinterpret_cast<FILE**>(stderr), "CONOUT$", "w", stderr);

				AttachConsole(GetProcessId((hModule)));

				SetConsoleTitle("My farm bot");

				// disable close button
				EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_DISABLED);
		}
}
using std::cout;
using std::endl;
char __fastcall Hook::hkSendPacket(int a1, int ebx, unsigned int a2, long** a3) {
		for (long i = 0; i < sizeof(a3); i++) {
				if (i == sizeof(a3) - 1)
						cout << static_cast<int>(reinterpret_cast<BYTE*>(a3)[i]) << endl;
				else if (i == 0)
						cout << "Packet header : " << static_cast<int>(reinterpret_cast<BYTE*>(a3)[i]) << ", ";
				else
						cout << static_cast<int>(reinterpret_cast<BYTE*>(a3)[i]) << ", ";
		}
		return GameFunc::SendPacket(a1, ebx, a2, a3);
}
#endif


bool Hook::Init() {
		if (GetD3D9Device() && GetD3D9InputDevice()) {
				// getting the pattern scanner instance to scan for patterns
				// in the game memory

#ifdef CONSOLE
				console(Data::g_hModule);
#endif
				Data::window = FindWindowA(NULL, "Elaris v1.0");
				oWndProc = (WndProc_t) SetWindowLongPtr(Data::window, GWL_WNDPROC, (LONG_PTR) Hook::WndProc);

				// direct x and direct input vTable initialization
				pEndScene = (EndScene_t) deviceTable[42];
				pReset = (Reset_t) deviceTable[16];
				pGetDeviceData = (GetDeviceData_t) inputDeviceTable[10];
				pGetDeviceState = (GetDeviceState_t) inputDeviceTable[9];

				// hook functions
				DetourTransactionBegin();
				DetourUpdateThread(GetCurrentThread());
				DetourAttach(&(PVOID&) pEndScene, EndScene);
				DetourAttach(&(PVOID&) pReset, Reset);
				DetourAttach(&(PVOID&) pGetDeviceData, GetDeviceData);
				DetourAttach(&(PVOID&) pGetDeviceState, GetDeviceState);
				DetourTransactionCommit();

				return true;
		}
		return false;
}

bool Hook::Shutdown() {
#ifdef CONSOLE
		FreeConsole();
#endif
		if (Gui::IsImGuiInit()) {
				ImGui_ImplDX9_Shutdown();
				ImGui_ImplWin32_Shutdown();
				ImGui::DestroyContext();
		}
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&) pEndScene, EndScene);
		DetourDetach(&(PVOID&) pReset, Reset);
		DetourDetach(&(PVOID&) pGetDeviceData, GetDeviceData);
		DetourDetach(&(PVOID&) pGetDeviceState, GetDeviceState);
		DetourTransactionCommit();
#ifdef CONSOLE
		DetourDetach(&(PVOID&) GameFunc::SendPacket, hkSendPacket);
#endif
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
		if (Gui::IsShowMenu()) {
				ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

				if (uMsg == WM_KEYDOWN) {
						switch (wParam) {
								case VK_INSERT:
										Gui::FlipMenu();
										break;
								case VK_END:
										Gui::FlipDetach();
										break;
						}
				}
				return TRUE;
		}
		if (uMsg == WM_KEYDOWN) {
				switch (wParam) {
						case VK_INSERT:
								Gui::FlipMenu();
								break;
						case VK_END:
								Gui::FlipDetach();
								break;
				}
		}
		return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall Hook::GetDeviceState(IDirectInputDevice8* pThis, DWORD cbData, LPVOID lpvData) {
		HRESULT result = pGetDeviceState(pThis, cbData, lpvData);
		if (result == DI_OK) {
				if (Gui::IsShowMenu()) {
						((LPDIMOUSESTATE2) lpvData)->rgbButtons[0] = 0;
						((LPDIMOUSESTATE2) lpvData)->rgbButtons[1] = 0;
				}
		}
		return result;
}

HRESULT __stdcall Hook::GetDeviceData(IDirectInputDevice8* pThis, DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags) {
		HRESULT result = pGetDeviceData(pThis, cbObjectData, rgdod, pdwInOut, dwFlags);
		if (result == DI_OK) {
				if (Gui::IsShowMenu()) {
						*pdwInOut = 0; //set array size 0
				}
		}
		return result;
}

HRESULT __stdcall Hook::EndScene(IDirect3DDevice9* pDevice) {
		// if we must unload the dll then we create a thread and exit
		if (Gui::IsDetach()) {
				CreateThread(nullptr, 0, dllFunctions::ExitThread, Data::g_hModule, 0, nullptr);
		}

		// if the device == null then we just return to the original function so we
		// don't initialise ImGui with a null device
		if (pDevice == NULL)
				return pEndScene(pDevice);

		if (!Gui::IsImGuiInit()) {
				Gui::FlipImGui();
				ImGui::CreateContext();
				ImGuiIO& io = ImGui::GetIO();
				ImGui_ImplWin32_Init(FindWindowA(NULL, "Elaris v1.0"));
				ImGui_ImplDX9_Init(pDevice);
		}

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		// here goes the menu

		if (Gui::IsShowMenu()) {
				Gui::RenderMenu();
		}
		if (Gui::IsShowCoords()) {
				Gui::RenderCoordWindow();
		}

		ImGui::EndFrame();
		ImGui::Render();

		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		return pEndScene(pDevice);
}

HRESULT __stdcall Hook::Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* params) {
		ImGui_ImplDX9_InvalidateDeviceObjects();
		const auto result = pDevice->Reset(params);
		if (result == D3DERR_INVALIDCALL) {
				IM_ASSERT(0);
		}
		ImGui_ImplDX9_CreateDeviceObjects();
		return pReset(pDevice, params);
}