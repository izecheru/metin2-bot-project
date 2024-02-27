#pragma once
#include <Windows.h>
#include "pointers.h"
#include "singleton.h"
#include "gameFunctions.h"
#include "entity.h"
// directx
#include "../ext/detours/detours.h"
#include "../ext/directx/Include/d3d9.h"
#include "../ext/directx/Include/d3dx9.h"


// imgui
#include "../ext/imgui/imgui.h"
#include "../ext/imgui/imgui_impl_dx9.h"
#include "../ext/imgui/imgui_impl_win32.h"


class Gui : public Singleton<Gui> {
public:
		bool showMenu = false;
		bool InitImGui = false;
		bool toDetach = false;
		bool blockMouse = false;
		bool blockKeyboard = false;
		bool canResize = false;
		bool showInstanceDetails = false;
		Entity* ent;
		GameFunc& gameFunc = GameFunc::getInstance();

		bool showCInstanceBase = false;
		bool canUseSkill = false;

		void FlipMenu();
		void FlipDetach();
		void FlipBlockMouse();
		void FlipBlockKeyboard();
		void FlipCanResize();

		bool IsShowMenu();
		bool IsDetach();
		bool IsImGuiInit();
		bool IsMouseBlocked();
		bool IsKeyboardBlocked();
		bool CanResize();

		void RenderVariable(void* value, const char* variableName);
		void RenderMenu();
};