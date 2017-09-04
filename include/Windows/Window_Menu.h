#pragma once
#include <Window.h>

namespace Szczur {
	class Window_Menu :public Window {
	private:
		int option;
		int options_count;
		sf::String options[9];
		
	public:
		Window_Menu();
		void Refresh();
		
		void OnKeyPress(Input::Key key);
		void OnMouseMove(int x, int y);
		void OnMouseClick(Input::Button button);
		void OnGainActive();
	};
}
