#pragma once
#include <Szczur/Window.h>
#include <list>

using namespace Szczur;

class Window_Items :public Window {
public:
	Window_Items();
	void refresh();
	
	void onKeyPress(Input::Key key);
	void onMouseMove(int x, int y);
	
private:
	int option;
	int options_count;
	std::list<const wchar_t*> options;
};
