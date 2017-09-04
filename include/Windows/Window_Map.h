#pragma once
#include <Window.h>
#include <Player.h>

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
