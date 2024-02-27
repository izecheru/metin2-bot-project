#include "gui.h"
#include "gameFunctions.h"
#include "entity.h"

void Gui::RenderMenu() {
		if (ImGui::GetIO().WantCaptureMouse == true) {
				ImGui::GetIO().MouseDrawCursor = true;
		} else {
				ImGui::GetIO().MouseDrawCursor = false;
		}

		// here are the menu tabs
		ImGui::Begin("cheeky little shit", nullptr, ImGuiWindowFlags_NoDecoration);
		ImGui::SetNextWindowPos(ImVec2(0, 20));

		if (ImGui::BeginTabBar("tabs")) {
				// main tab
				if (ImGui::BeginTabItem("main")) {
						RenderVariable((void*) ptr::CPythonCharacterManager, "CPythonCharacterManager: ");
						RenderVariable((void*) ptr::CPythonNetworkStream, "CPythonNetworkStream: ");
						RenderVariable((void*) ptr::CFlyingManager, "CFlyingManager: ");
						RenderVariable((void*) ptr::CRaceManager, "CRaceManager: ");
						RenderVariable((void*) ptr::CPythonItem, "CPythonItem: ");
						RenderVariable((void*) ptr::CItemManager, "CItemManager: ");
						ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("second")) {
						if (ImGui::Button("get the main instance ptr")) {
								ent = gameFunc.GetMainInstancePtr(*(void**) ptr::CPythonCharacterManager);
								showInstanceDetails = true;
						}
						if (showInstanceDetails) {
								ImGui::Text("%p ", ent);
								ImGui::Text("%s ", ent->name);
								ImGui::Text("%.2f %.2f %.2f ", ent->position.x, ent->position.y, ent->position.z);
						}
						ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
		}
		ImGui::End();
}

void Gui::RenderVariable(void* value, const char* variableName) {
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