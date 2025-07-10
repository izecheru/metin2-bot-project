#pragma once
#include "singleton.h"

class UserInterface :public Singleton<UserInterface>
{
private:

  bool showMenu;
  bool showValue;
  bool InitImGui;
  bool toDetach;
  bool blockMouse;
  bool blockKeyboard;
  bool canResize;
  bool showInstanceDetails;
  bool entitiesInit;
  bool showCInstanceBase;
  bool canUseSkill;
  bool guiInit;
  bool applyMetinSlider;

public:

  void init();
  void flipMenu();
  void flipDetach();
  void setMouseBlock();
  void setKeyboardBlock();
  void setCanResize();
  void setImGuiInit();
  void setShowCoordinatesWin();
  bool isCoordinatesWinVisible()const;
  bool isMenuVisible()const;
  bool isDetached();
  bool isImGuiInit();
  bool isMouseBlocked();
  bool isKeyboardBlocked();
  bool isResizable();
  void renderVar(int& value, const char* variableName);
  void renderMenu();
  void renderCoordinatesWin();
};
