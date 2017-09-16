#pragma once
#include <Szczur/Window.h>
#include <SzczurEngine/Player.h>
#include <SzczurEngine/Events/EventPage.h>

namespace Szczur {
	class Window_Map :public Window {
	public:
		Window_Map();
		void refresh();
		void update();
		void onKeyPress(Input::Key key);
		void onGainActive();
		void onLostActive();
		void onClosed();
		
	private:
		Event* activeEvent;
	};
}
