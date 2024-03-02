#pragma once
#include <Windows.h>
#include "pointers.h"
#include "singleton.h"
#include "gameFunctions.h"
#include "entity.h"
// directx
#include "../ext/directx/Include/d3d9.h"
#include "../ext/directx/Include/d3dx9.h"


// imgui
#include "../ext/imgui/imgui.h"
#include "../ext/imgui/imgui_impl_dx9.h"
#include "../ext/imgui/imgui_impl_win32.h"


class Gui {
		inline static bool showMenu;
		inline static bool showCoords;
		inline static bool InitImGui;
		inline static bool toDetach;
		inline static bool blockMouse;
		inline static bool blockKeyboard;
		inline static bool canResize;
		inline static bool showInstanceDetails;
		inline static bool entitiesInit;
		inline static TCharacterInstanceMap entities;
		inline static Entity* ent;
		inline static bool showCInstanceBase;
		inline static bool canUseSkill;
		inline static bool guiInit;
		inline static bool applyMetinSlider;

public:
		static void Init();

		static void FlipMenu();
		static void FlipDetach();
		static void FlipBlockMouse();
		static void FlipBlockKeyboard();
		static void FlipCanResize();
		static void FlipImGui();
		static void FlipShowCoords();


		static bool IsShowCoords();
		static bool IsShowMenu();
		static bool IsDetach();
		static bool IsImGuiInit();
		static bool IsMouseBlocked();
		static bool IsKeyboardBlocked();
		static bool CanResize();

		static void RenderVariable(int value, const char* variableName);
		static void RenderMenu();
		static void RenderCoordWindow();
};