/*#pragma once
#include <Szczur/Window.h>
#include <SFML/System/String.hpp>
#include <list>

namespace Szczur {
	class Window_Menu :public Window {
	public:
		Window_Menu();
		void refresh();
		
		void onKeyPress(Input::Key key);
		void onMouseMove(int x, int y);
		void onMouseClick(Input::Button button);
		void onGainActive();
		
	private:
		int option;
		int options_count;
		sf::String options[9];
	};
}*/
