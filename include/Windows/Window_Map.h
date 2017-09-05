#pragma once
#include <Szczur/Window.h>
#include <Szczur/Map/Player.h>

namespace Szczur {
	class Window_Map :public Window {
	public:
		Player player;
	
		Window_Map();
		void Refresh();
		void OnKeyPress(Input::Key key);
		void OnGainActive();
		void OnLostActive();
	};
}
