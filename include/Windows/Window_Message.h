#pragma once
#include <Szczur/Window.h>
#include <Szczur/Events/Commands/CMD_Message.h>
#include <string>

namespace Szczur {
	class Window_Message :public Window {
	private:
		CMD_Message* message;
		float time;
		float maxTime;
		int letters;
	
	public:
		Window_Message(CMD_Message* message);
		
		void Refresh();
		
		void Update();
		void OnKeyPress(Input::Key key);
		void OnClosed();
	};
}
