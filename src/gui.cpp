#include "../ext/imgui/imgui.h"
#include "gameFunctions.h"
#include "gui.h"

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

/// Renders the primary menu
void Gui::RenderMenu()
{
		ImGui::Begin("Metin bot", nullptr, ImGuiWindowFlags_NoDecoration);
		ImGui::SetWindowSize(ImVec2(500, 500));
		if (ImGui::BeginTabBar("tabs"))
		{
				if (ImGui::BeginTabItem("Pointers addresses"))
				{
						if (ImGui::Button("Test function"))
						{
							GameFunction::SendItemUsePacket(1);
						}
						ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
		}
		ImGui::End();
}

void Gui::RenderVariable(const int value, const char* variableName)
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
