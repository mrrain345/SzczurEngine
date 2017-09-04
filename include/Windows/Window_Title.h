#pragma once
#include <Window.h>

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
	};
}
