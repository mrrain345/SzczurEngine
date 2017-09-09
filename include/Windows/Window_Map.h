#pragma once
#include <Szczur/Window.h>
#include <Szczur/Map/Player.h>
#include <Szczur/Events/EventPage.h>

namespace Szczur {
	class Window_Map :public Window {
	private:
		Event* activeEvent;
		
	public:
		Window_Map();
		void Refresh();
		void Update();
		void OnKeyPress(Input::Key key);
		void OnGainActive();
		void OnLostActive();
		void OnClosed();
	};
}
