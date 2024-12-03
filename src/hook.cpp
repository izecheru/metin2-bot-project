#include "hook.h"
#include "scanner.h"

#define CONSOLE1
#ifdef CONSOLE
/// <summary>
/// Allocs a console to which we can print stuff from the program
/// </summary>
/// <param name="hModule">The handle to our process</param>
static void console(LPVOID hModule)
{ // console assignment
		if (AllocConsole())
		{
				freopen_s(&Hook::fConsole, "CONOUT$", "w",
									stdout); // have to use freopen_s instead of freopen to get
				// ride of the _CRT_SECURE_NO_WARNINGS message
				freopen_s(&Hook::fConsole, "CONIN$", "r", stdin);
				freopen_s(&Hook::fConsole, "CONOUT$", "w", stderr);

				AttachConsole(GetProcessId((hModule)));

				SetConsoleTitle("My farm bot");

				// disable close button
				EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE,
											 MF_DISABLED);
		}
}

using std::cout;
using std::endl;
#endif

bool Hook::Init()
{
		if (GetD3D9Device() && GetD3D9InputDevice())
		{
#ifdef CONSOLE
				console(Data::g_hModule);
#endif
				Data::window = FindWindowA(nullptr, Data::chModule);
				oWndProc = reinterpret_cast<WndProc_t>(SetWindowLongPtr(Data::window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Hook::WndProc)));

				// direct x and direct input vTable initialization
				pEndScene = reinterpret_cast<EndScene_t>(deviceTable[42]);
				pReset = reinterpret_cast<Reset_t>(deviceTable[16]);
				pGetDeviceData = reinterpret_cast<GetDeviceData_t>(inputDeviceTable[10]);
				pGetDeviceState = reinterpret_cast<GetDeviceState_t>(inputDeviceTable[9]);

				// hook functions
				DetourTransactionBegin();
				DetourUpdateThread(GetCurrentThread());

				DetourAttach(&reinterpret_cast<PVOID&>(pEndScene), EndScene);
				DetourAttach(&reinterpret_cast<PVOID&>(pReset), Reset);
				DetourAttach(&reinterpret_cast<PVOID&>(pGetDeviceData), GetDeviceData);
				DetourAttach(&reinterpret_cast<PVOID&>(pGetDeviceState), GetDeviceState);
				DetourTransactionCommit();

				return true;
		}
		return false;
}

bool Hook::Shutdown()
{
		if (Gui::IsImGuiInit())
		{
				ImGui_ImplDX9_Shutdown();
				ImGui_ImplWin32_Shutdown();
				ImGui::DestroyContext();
		}
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());

		DetourDetach(&reinterpret_cast<PVOID&>(pEndScene), EndScene);
		DetourDetach(&reinterpret_cast<PVOID&>(pReset), Reset);
		DetourDetach(&reinterpret_cast<PVOID&>(pGetDeviceData), GetDeviceData);
		DetourDetach(&reinterpret_cast<PVOID&>(pGetDeviceState), GetDeviceState);
		DetourTransactionCommit();

		SetWindowLongPtr(Data::window, GWLP_WNDPROC, (LONG_PTR) oWndProc);

#ifdef CONSOLE
		// Closign the console window
		if (fConsole)
				fclose(fConsole);

		FreeConsole();
#endif // CONSOLE

		return true;
}

/// <summary>
/// Get the pointer to the D3D9 input device to get the input method and block
/// clicks if menu is enabled
/// </summary>
/// <returns>True or false if the process works correctly</returns>
bool Hook::GetD3D9InputDevice()
{
		IDirectInput8* pDirectInput = nullptr;
		if (DirectInput8Create(
				Data::g_hModule, DIRECTINPUT_VERSION, IID_IDirectInput8,
				reinterpret_cast<LPVOID*>(&pDirectInput), nullptr) != DI_OK)
		{
				return false;
		}
		LPDIRECTINPUTDEVICE8 lpdiMouse;
		if (pDirectInput->CreateDevice(GUID_SysMouse, &lpdiMouse, nullptr) != DI_OK)
		{
				pDirectInput->Release();
				return false;
		}
		inputDeviceTable = *reinterpret_cast<void***>(lpdiMouse);
		pDirectInput->Release();
		lpdiMouse->Release();
		return true;
}

/// Get the pointer to the D3D9 device to hook the endscene and reset functions
/// <returns>True or false if the process works correctly</returns>
bool Hook::GetD3D9Device()
{
		IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
		if (!pD3D)
		{
				return false;
		}

		const HWND tmpWnd = CreateWindowA(
				"BUTTON", "Temp Window", WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT,
				CW_USEDEFAULT, 300, 300, nullptr, nullptr, Data::g_hModule, nullptr);
		if (tmpWnd == nullptr)
		{
				return false;
		}
		D3DPRESENT_PARAMETERS d3dpp = { 0 };
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = tmpWnd;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		IDirect3DDevice9* pDevice = nullptr;
		if (const HRESULT result = pD3D->CreateDevice(
				D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, tmpWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDevice);
				FAILED(result) || !pDevice)
		{
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

LRESULT WINAPI Hook::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam,
														 LPARAM lParam)
{
		if (Gui::IsShowMenu())
		{
				ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

				if (uMsg == WM_KEYDOWN)
				{
						switch (wParam)
						{
								case VK_INSERT:
										Gui::FlipMenu();
										break;
								case VK_END:
										Gui::FlipDetach();
										break;
								default:
										break;
						}
				}
				return TRUE;
		}
		if (uMsg == WM_KEYDOWN)
		{
				switch (wParam)
				{
						case VK_INSERT:
								Gui::FlipMenu();
								break;
						case VK_END:
								Gui::FlipDetach();
								break;
						default:
								break;
				}
		}
		return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall Hook::GetDeviceState(IDirectInputDevice8* pThis, DWORD cbData, LPVOID lpvData)
{
		HRESULT result = pGetDeviceState(pThis, cbData, lpvData);
		if (result == DI_OK)
		{
				if (Gui::IsShowMenu())
				{
						((LPDIMOUSESTATE2) lpvData)->rgbButtons[0] = 0;
						((LPDIMOUSESTATE2) lpvData)->rgbButtons[1] = 0;
				}
		}
		return result;
}

HRESULT __stdcall Hook::GetDeviceData(IDirectInputDevice8* pThis,
																			DWORD cbObjectData,
																			LPDIDEVICEOBJECTDATA rgdod,
																			const LPDWORD pdwInOut,
																			const DWORD dwFlags)
{
		const HRESULT result =
				pGetDeviceData(pThis, cbObjectData, rgdod, pdwInOut, dwFlags);
		if (result == DI_OK)
		{
				// we block input if menu is visible
				if (Gui::IsShowMenu())
				{
						*pdwInOut = 0; // set array size 0
				}
		}
		return result;
}

HRESULT __stdcall Hook::EndScene(IDirect3DDevice9* pDevice)
{
		if (Gui::IsDetach())
		{
				CreateThread(nullptr, 0, DllFunctions::ExitThread, Data::g_hModule, 0, nullptr);
		}

		// if the device == null then we just return to the original function so we
		// don't initialise ImGui with a null device and cause a crash
		if (pDevice == nullptr)
				return pEndScene(pDevice);

		if (!Gui::IsImGuiInit())
		{
				Gui::FlipImGui();
				ImGui::CreateContext();
				ImGui::GetIO();
				// ImGui_ImplWin32_Init(FindWindowA(nullptr, "Elaris v1.0"));
				ImGui_ImplWin32_Init(FindWindowA(nullptr, Data::chModule));
				ImGui_ImplDX9_Init(pDevice);
		}

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// show menu
		if (Gui::IsShowMenu())
		{
				Gui::RenderMenu();
		}

		// a special window for my character coords
		if (Gui::IsShowCoords())
		{
				Gui::RenderCoordWindow();
		}

		ImGui::EndFrame();
		ImGui::Render();

		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		return pEndScene(pDevice);
}

// This function might be crucial to imgui reinitialization if it gets
// destroyed along the way by the program or something happens
HRESULT __stdcall Hook::Reset(IDirect3DDevice9* pDevice,
															D3DPRESENT_PARAMETERS* params)
{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		if (const auto result = pDevice->Reset(params);
				result == D3DERR_INVALIDCALL)
		{
				IM_ASSERT(0);
		}
		ImGui_ImplDX9_CreateDeviceObjects();
		return pReset(pDevice, params);
}