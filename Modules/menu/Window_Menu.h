#pragma once
#include <Szczur/Window.h>
#include <list>

using namespace Szczur;

struct MenuOption {
	uint32_t owner;
	size_t id;
	bool active;
	int position;
	wchar_t* option;
	void(*callback)(size_t id);
};

class Window_Menu :public Window {
public:
	Window_Menu();
	void refresh();
	
	static int addOption(MenuOption* option);
	
	void onKeyPress(Input::Key key);
	void onMouseMove(int x, int y);
	void onMouseClick(Input::Button button);
	void onGainActive();
	
private:
	int option;
	static std::list<MenuOption*> options;
};

extern Window_Menu* window_menu;
