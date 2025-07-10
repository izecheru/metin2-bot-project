#include "gui.h"
#include "../ext/imgui/imgui.h"
#include "gamePointers.h"

void UserInterface::init()
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
void UserInterface::renderCoordinatesWin()
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
void UserInterface::renderMenu()
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
      ImGui::Separator();
    }
    ImGui::EndTabBar();
  }
  ImGui::End();
}

void UserInterface::renderVar(int& value, const char* variableName)
{
  ImGui::Text("%s - %p", variableName, value);
}

bool UserInterface::isMenuVisible()const
{
  return showMenu == true;
}

bool UserInterface::isDetached()
{
  return toDetach == true;
}

bool UserInterface::isImGuiInit()
{
  return InitImGui == true;
}

bool UserInterface::isMouseBlocked()
{
  return blockMouse == true;
}

bool UserInterface::isKeyboardBlocked()
{
  return blockKeyboard == true;
}

bool UserInterface::isResizable()
{
  return canResize == true;
}

void UserInterface::flipMenu()
{
  showMenu = !showMenu;
}

void UserInterface::flipDetach()
{
  toDetach = !toDetach;
}

void UserInterface::setMouseBlock()
{
  blockMouse = !blockMouse;
}

void UserInterface::setKeyboardBlock()
{
  blockKeyboard = !blockKeyboard;
}

void UserInterface::setCanResize()
{
  canResize = !canResize;
}

void UserInterface::setImGuiInit()
{
  InitImGui = true;
}

bool UserInterface::isCoordinatesWinVisible()const
{
  return showValue == true;
}

void UserInterface::setShowCoordinatesWin()
{
  showValue = !showValue;
}