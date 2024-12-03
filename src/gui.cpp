#include "gui.h"
#include "../ext/imgui/imgui.h"
#include "gamePointers.h"

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
		showValue = false;
}

/// <summary>
/// Coordinates window, used it for my own coordinates
/// Will leave it here as a window example
/// </summary>
void Gui::RenderCoordWindow()
{
		ImGui::Begin("window 1", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

		// to make sure we open the window in the application view
		RECT rect = { NULL };
		int x; int y;
		if (GetWindowRect(GetConsoleWindow(), &rect))
		{
				x = rect.left;
				y = rect.top;
		}

		ImGui::SetWindowPos(ImVec2(100, 100));
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
		// to make sure we open the window in the application view
		RECT rect = { NULL };
		int x; int y;
		if (GetWindowRect(GetConsoleWindow(), &rect))
		{
				x = rect.left / 2;
				y = rect.top / 2;
		}

		ImGui::SetWindowPos(ImVec2(100, 100));
		ImGui::SetWindowSize(ImVec2(500, 500));
		if (ImGui::BeginTabBar("Tabs"))
		{
				if (ImGui::BeginTabItem("Pointers addresses"))
				{
						ImGui::Text("CPythonNetworkStream  = %04x", GamePointers::CPythonNetworkStream);
						ImGui::Text("CPythonCharacterManager = %04x", GamePointers::CPythonCharacterManager);
						ImGui::Text("kalive size = %d", GamePointers::kAliveInstance.size());
						ImGui::Separator();
						if (!GamePointers::kAliveInstance.empty())
								for (auto i = GamePointers::kAliveInstance.begin(); i != GamePointers::kAliveInstance.end(); i++)
								{
										if (!i->first)
												continue;

										ImGui::Text("name -> %s", i->second->entityName);
								}

						ImGui::Separator();
						/*ImGui::Text("mob entitites -> %d", GamePointers::mobArray.size());
						for (int i = 0; i < GamePointers::mobArray.size(); i++)
						{
								if (!GamePointers::mobArray.at(i))
										continue;

								if (sizeof(GamePointers::mobArray.at(i)) != sizeof(Entity::Mob))
										continue;

								ImGui::Text("name -> %s", GamePointers::mobArray.at(i)->entityName);
						}

						ImGui::EndTabItem();*/
				}
				ImGui::EndTabBar();
		}
		ImGui::End();
}

void Gui::RenderVariable(const int value, const char* variableName)
{
		ImGui::Text("%s - %p", variableName, value);
}

bool Gui::IsShowMenu() { return showMenu == true; }

bool Gui::IsDetach() { return toDetach == true; }

bool Gui::IsImGuiInit() { return InitImGui == true; }

bool Gui::IsMouseBlocked() { return blockMouse == true; }

bool Gui::IsKeyboardBlocked() { return blockKeyboard == true; }

bool Gui::CanResize() { return canResize == true; }

void Gui::FlipMenu() { showMenu = !showMenu; }

void Gui::FlipDetach() { toDetach = !toDetach; }

void Gui::FlipBlockMouse() { blockMouse = !blockMouse; }

void Gui::FlipBlockKeyboard() { blockKeyboard = !blockKeyboard; }

void Gui::FlipCanResize() { canResize = !canResize; }

void Gui::FlipImGui() { InitImGui = true; }

bool Gui::IsShowCoords() { return showValue == true; }

void Gui::FlipShowCoords() { showValue = !showValue; }