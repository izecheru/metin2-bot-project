#include <vector>
#include "patch.h"
#include "gui.h"
#include "gameFunctions.h"
#include "entity.h"
#include "cheatVars.h"

void Gui::Init() {
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

void Gui::RenderCoordWindow() {
		ImGui::Begin("window 1", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		ImGui::SetWindowPos(ImVec2(100, 10));
		ImGui::SetWindowSize(ImVec2(250, 49));
		if (ImGui::GetIO().WantCaptureMouse == true) {
				ImGui::GetIO().MouseDrawCursor = true;
		} else {
				ImGui::GetIO().MouseDrawCursor = false;
		}
		//ImGui::Text("%p ", ent);
		ImGui::Text("%s ", ent->name);
		ImGui::Text("%.2f %.2f %.2f ", ent->position.x, ent->position.y, ent->position.z);
		ImGui::End();
}

void Gui::RenderMenu() {
		if (!entitiesInit) {
				entities = (TCharacterInstanceMap*) (Pointer::CPythonCharacterManager + 0xc);
				if (entities != nullptr)
						entitiesInit = true;
		}
		// here are the menu tabs
		ImGui::Begin("cheeky little shit", nullptr, ImGuiWindowFlags_NoDecoration);

		if (ImGui::BeginTabBar("tabs")) {
				// main 

				if (ImGui::BeginTabItem("main")) {
						if (ImGui::SliderInt("Metin limit autofarm ", &Var::metinLimit, 0, 200, "%d", ImGuiSliderFlags_AlwaysClamp)) {
								if (ImGui::IsItemDeactivatedAfterEdit() && applyMetinSlider) {
										applyMetinSlider = false;
								}
						}
						/*if (ImGui::Button("Main instance")) {
								ent = GameFunc::GetMainInstancePtr(*(void**) Pointer::CPythonCharacterManager);
								if (ent != nullptr) {
										showInstanceDetails = true;
										showCoords = true;
								}
						}*/
						ImGui::EndTabItem();
				}

				////second tab
				//if (ImGui::BeginTabItem("second")) {
				//		if (ImGui::Button("get the main instance ptr")) {
				//				ent = GameFunc::GetMainInstancePtr(*(void**) Pointer::CPythonCharacterManager);
				//				if (ent != nullptr) {
				//						showInstanceDetails = true;
				//				}
				//		}


				//		ImGui::EndTabItem();
				//}
				ImGui::EndTabBar();
		}
		ImGui::End();
}

void Gui::RenderVariable(int value, const char* variableName) {
		ImGui::Text("%s - %p", variableName, value);
}

bool Gui::IsShowMenu() {
		return showMenu == true;
}

bool Gui::IsDetach() {
		return toDetach == true;
}

bool Gui::IsImGuiInit() {
		return InitImGui == true;
}

bool Gui::IsMouseBlocked() {
		return blockMouse == true;
}

bool Gui::IsKeyboardBlocked() {
		return blockKeyboard == true;
}

bool Gui::CanResize() {
		return canResize == true;
}

void Gui::FlipMenu() {
		showMenu = !showMenu;
}

void Gui::FlipDetach() {
		toDetach = !toDetach;
}

void Gui::FlipBlockMouse() {
		blockMouse = !blockMouse;
}

void Gui::FlipBlockKeyboard() {
		blockKeyboard = !blockKeyboard;
}

void Gui::FlipCanResize() {
		canResize = !canResize;
}

void Gui::FlipImGui() {
		InitImGui = true;
}

bool Gui::IsShowCoords() {
		return showCoords == true;
}

void Gui::FlipShowCoords() {
		showCoords = !showCoords;
}