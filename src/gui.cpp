#include "classPointers.h"
#include "entity.h"
#include "gameFunctions.h"
#include "gui.h"
#include <vector>
// directx
#include "../ext/directx/Include/d3d9.h"
#include "../ext/directx/Include/d3dx9.h"


// imgui
#include "../ext/imgui/imgui.h"
#include "../ext/imgui/imgui_impl_dx9.h"
#include "../ext/imgui/imgui_impl_win32.h"

void Gui::Init()
{
		guiInit = false;
		showMenu = false;
		InitImGui = false;
		toDetach = false;
		blockMouse = false;
		blockKeyboard = false;
		canResize = false;
		showInstanceDetails = false;
		entitiesInit = false;
		showCInstanceBase = false;
		canUseSkill = false;
		applyMetinSlider = false;
		showCoords = false;
}

/// <summary>
/// Coordinates window, used it for my own coordinates
/// Will leave it here as a window example
/// </summary>
void Gui::RenderCoordWindow()
{
		ImGui::Begin("window 1", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		ImGui::SetWindowPos(ImVec2(100, 10));
		ImGui::SetWindowSize(ImVec2(250, 49));
		if (ImGui::GetIO().WantCaptureMouse == true)
		{
				ImGui::GetIO().MouseDrawCursor = true;
		}
		else
		{
				ImGui::GetIO().MouseDrawCursor = false;
		}

		ImGui::End();
}

/// <summary>
/// Renders the primary menu
/// </summary>
void Gui::RenderMenu()
{
		ImGui::Begin("cheeky little shit", nullptr, ImGuiWindowFlags_NoDecoration);
		ImGui::SetWindowSize(ImVec2(500, 500));
		if (ImGui::BeginTabBar("tabs"))
		{
				if (ImGui::BeginTabItem("Pointers addresses"))
				{
						if (ImGui::Button("Test function"))
						{
								for (int i = 1; i <= 5; i++)
								{
										GameFunction::SendItemUsePacket(i);
								}
						}
						ImGui::Text("CPythonCharacterManager %p", ClassPointers::CPythonCharacterManager);
						ImGui::Text("Dref CPythonCharacterManager %p", *(void**)ClassPointers::CPythonCharacterManager);
						ImGui::Text("CPythonPlayer %p", ClassPointers::CPythonPlayer);
						ImGui::Text("CRaceManager %p", ClassPointers::CRaceManager);
						ImGui::Text("CFlyingManager %p", ClassPointers::CFlyingManager);
						ImGui::Text("CPythonNetworkStream %p", ClassPointers::CPythonNetworkStream);
						ImGui::Text("CPythonPlayer %p", ClassPointers::CPythonPlayer);
						ImGui::Text("CPythonItem %p", ClassPointers::CPythonItem);
						ImGui::Text("CInstanceBase %p", ClassPointers::CInstanceBase);
						ImGui::Text("CItemManager %p", ClassPointers::CItemManager);
						ImGui::Text("CPythonBackground %p", ClassPointers::CPythonBackground);
						ImGui::Text("CPythonMiniMap %p", ClassPointers::CPythonMiniMap);
						ImGui::Text("Function use item %p", GameFunction::pSendItemUsePacket);

						ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
		}
		ImGui::End();
}

void Gui::RenderVariable(int value, const char* variableName)
{
		ImGui::Text("%s - %p", variableName, value);
}

bool Gui::IsShowMenu()
{
		return showMenu == true;
}

bool Gui::IsDetach()
{
		return toDetach == true;
}

bool Gui::IsImGuiInit()
{
		return InitImGui == true;
}

bool Gui::IsMouseBlocked()
{
		return blockMouse == true;
}

bool Gui::IsKeyboardBlocked()
{
		return blockKeyboard == true;
}

bool Gui::CanResize()
{
		return canResize == true;
}

void Gui::FlipMenu()
{
		showMenu = !showMenu;
}

void Gui::FlipDetach()
{
		toDetach = !toDetach;
}

void Gui::FlipBlockMouse()
{
		blockMouse = !blockMouse;
}

void Gui::FlipBlockKeyboard()
{
		blockKeyboard = !blockKeyboard;
}

void Gui::FlipCanResize()
{
		canResize = !canResize;
}

void Gui::FlipImGui()
{
		InitImGui = true;
}

bool Gui::IsShowCoords()
{
		return showCoords == true;
}

void Gui::FlipShowCoords()
{
		showCoords = !showCoords;
}