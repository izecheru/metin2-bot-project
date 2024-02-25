#include "gui.h"
#include "dllFunctions.h"
#include "data.h"

HRESULT __stdcall Gui::EndScene(IDirect3DDevice9* pDevice) {
		// if we must unload the dll then we create a thread and exit
		if (toDetach) {
				CreateThread(nullptr, 0, dllFunctions::ExitThread, Data::g_hModule, 0, nullptr);
		}

		// if the device == null then we just return to the original function so we
		// don't initialise ImGui with a null device
		if (pDevice == NULL)
				return pEndScene(pDevice);

		if (!Gui::InitImGui) {
				Gui::InitImGui = true;
				ImGui::CreateContext();
				ImGuiIO& io = ImGui::GetIO();
				ImGui_ImplWin32_Init(FindWindowA(NULL, "Elaris v1.0"));
				ImGui_ImplDX9_Init(pDevice);
		}

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		// here goes the menu
		if (showMenu) {
				RenderVariable((void*) Pointers::ptrCPythonNetworkStream, "CPythonNetworkStream class ");
				RenderVariable((void*) Pointers::printAddressForTest, "UseSkill function ");
		}

		ImGui::EndFrame();
		ImGui::Render();

		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		return pEndScene(pDevice);
}

HRESULT __stdcall Gui::Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* params) {
		ImGui_ImplDX9_InvalidateDeviceObjects();
		const auto result = pDevice->Reset(params);
		if (result == D3DERR_INVALIDCALL) {
				IM_ASSERT(0);
		}
		ImGui_ImplDX9_CreateDeviceObjects();
		return pReset(pDevice, params);
}

void Gui::RenderVariable(void* value, const char* variableName) {
		ImGui::Text("%s - %p", variableName, value);
}

bool Gui::IsShowMenu() {
		return showMenu == true;
}

bool Gui::IsToDetach() {
		return toDetach == true;
}

bool Gui::IsImGuiInit() {
		return InitImGui == true;
}

bool Gui::IsBlockedMouse() {
		return blockMouse == true;
}

bool Gui::IsBlockedKeyboard() {
		return blockKeyboard == true;
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