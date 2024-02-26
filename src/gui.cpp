#include "gui.h"

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
		ImGui::Begin("cheeky little shit");
		if (ImGui::BeginTabBar("tabs")) {
				// main tab
				if (ImGui::BeginTabItem("main")) {
						RenderVariable((void*) ptr::ptrCPythonCharacterManager, "Character manager: ");
						RenderVariable((void*) ptr::ptrCPythonNetworkStream, "Network stream: ");
				}
				ImGui::EndTabItem();
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