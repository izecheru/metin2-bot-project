#pragma once
#include <Windows.h>
#include "pointers.h"

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
		inline bool showMenu = false;
		inline bool InitImGui = false;
		inline bool toDetach = false;
		inline bool blockMouse = false;
		inline bool blockKeyboard = false;

		void FlipMenu();
		void FlipDetach();
		void FlipBlockMouse();
		void FlipBlockKeyboard();

		bool IsShowMenu();
		bool IsToDetach();
		bool IsImGuiInit();
		bool IsBlockedMouse();
		bool IsBlockedKeyboard();

		inline EndScene_t pEndScene = nullptr;
		inline Reset_t pReset = nullptr;
		void RenderVariable(void* value, const char* variableName);
		HRESULT __stdcall EndScene(IDirect3DDevice9* pDevice);
		HRESULT __stdcall Reset(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
};