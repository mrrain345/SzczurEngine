#pragma once
#include <Szczur/Window.h>
#include <Windows/Window_Map.h>

#define _USE_MATH_DEFINES
#include <cmath>

namespace Szczur {
	class Window_Title :public Window {
	public:
		Window_Title();
		void refresh();
		
		void onMousePress(Input::Button button);
		void onMouseMove(int x, int y);
		void onMouseRelease(Input::Button button);
		
		void onKeyPress(Input::Key key);
		void update();
		
	private:
		int option;
		int options_count;
		sf::String options[9];
	};
}
