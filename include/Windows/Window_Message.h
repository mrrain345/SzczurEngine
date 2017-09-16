#pragma once
#include <Szczur/Window.h>
#include <SzczurEngine/Events/Commands/CMD_Message.h>
#include <string>

namespace Szczur {
	class Window_Message :public Window {
	public:
		Window_Message(CMD_Message* message);
		
		void refresh();
		
		void update();
		void onKeyPress(Input::Key key);
		void onClosed();
		
	private:
		CMD_Message* message;
		float time;
		float maxTime;
		int letters;
	};
}
