#pragma once
#include <Windows.h>

// directx
#include "../ext/detours/detours.h"
#include "../ext/directx/Include/d3d9.h"
#include "../ext/directx/Include/d3dx9.h"


// imgui
#include "../ext/imgui/imgui.h"
#include "../ext/imgui/imgui_impl_dx9.h"
#include "../ext/imgui/imgui_impl_win32.h"

using EndScene_t = HRESULT(__stdcall*)(IDirect3DDevice9* pDevice);
using Reset_t = HRESULT(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);

namespace Gui {
		inline EndScene_t pEndScene = nullptr;
		HRESULT __stdcall EndScene(IDirect3DDevice9* pDevice);

		inline Reset_t pReset;
		HRESULT __stdcall Reset(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);

		inline bool showMenu = false;
		inline bool InitImGui = false;
		inline bool toDetach = false;
		inline bool blockMouse = false;
		inline bool blockKeyboard = false;
}