#pragma once
#include <Szczur/Window.h>
#include <Windows/Window_Map.h>

#define _USE_MATH_DEFINES
#include <cmath>

namespace Szczur {
	class Window_Title :public Window {
	private:
		int option;
		int options_count;
		sf::String options[9];
		
	public:
		Window_Title();
		void Refresh();
		
		void OnKeyPress(Input::Key key);
		void Update();
	};
}
