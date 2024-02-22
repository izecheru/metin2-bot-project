#include "gui.h"

HRESULT __stdcall Gui::EndScene(IDirect3DDevice9* pDevice) {
		if (pDevice == NULL)
				return pEndScene(pDevice);

		if (!Gui::InitImGui) {
				Gui::InitImGui = true;
				ImGui::CreateContext();

				ImGui_ImplWin32_Init(FindWindowA(NULL, "Elaris v1.0"));
				ImGui_ImplDX9_Init(pDevice);
		}

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		if (showMenu) {
				ImGui::ShowDemoWindow();
		}

		ImGui::EndFrame();
		ImGui::Render();

		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		return pEndScene(pDevice);
}

HRESULT __stdcall Gui::Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* params) {
		return pReset(pDevice, params);
}