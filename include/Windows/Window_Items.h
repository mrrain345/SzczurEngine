#pragma once
#include <Window.h>

namespace Szczur {
	class Window_Items :public Window {
	private:
		int option;
		int options_count;
		sf::String options[9];
		
	public:
		Window_Items();
		void Refresh();
		
		void OnKeyPress(Input::Key key);
		void OnMouseMove(int x, int y);
	};
}
