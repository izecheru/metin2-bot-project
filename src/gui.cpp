#include "gui.h"
#include "gameFunctions.h"

void Gui::RenderMenu() {
		if (ImGui::GetIO().WantCaptureMouse == true) {
				ImGui::GetIO().MouseDrawCursor = true;
		} else {
				ImGui::GetIO().MouseDrawCursor = false;
		}

		// if we want the window to be resized to 600 by 400 as soon as we resize it manually
		// same behaviour for the opacity
		if (!CanResize()) {
				ImGui::SetNextWindowSize(ImVec2(600, 400));
				ImGui::SetNextWindowBgAlpha(0.8);
		}
		// here are the menu tabs
		ImGui::Begin("cheeky little shit", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);
		if (ImGui::BeginTabBar("tabs")) {
				// main tab
				if (ImGui::BeginTabItem("main")) {
						RenderVariable((void*) ptr::CPythonCharacterManager, "CPythonCharacterManager: ");
						RenderVariable((void*) ptr::CPythonNetworkStream, "CPythonNetworkStream: ");
						RenderVariable((void*) ptr::CFlyingManager, "CFlyingManager: ");
						RenderVariable((void*) ptr::CRaceManager, "CRaceManager: ");
						RenderVariable((void*) ptr::CPythonItem, "CPythonItem: ");
						RenderVariable((void*) ptr::CItemManager, "CItemManager: ");
						RenderVariable((void*) ptr::test, "?: ");
						ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("second")) {
						ImGui::Checkbox("get the main instance ptr", &showText);
						if (showText) {
								ImGui::Text(" %p", gameFunc.GetMainInstancePtr(*(void**) ptr::CPythonCharacterManager));
								ImGui::Text("(void*) %p", (void*) gameFunc.GetMainInstancePtr(*(void**) ptr::CPythonCharacterManager));
								ImGui::Text("*(int*) %p", *(int*) gameFunc.GetMainInstancePtr(*(void**) ptr::CPythonCharacterManager));
								ImGui::Text("*(int**) %p", *(int**) gameFunc.GetMainInstancePtr(*(void**) ptr::CPythonCharacterManager));
								ImGui::Text("function address %p", gameFunc.GetMainInstancePtr);
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