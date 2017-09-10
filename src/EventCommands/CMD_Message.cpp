#include <Szczur/Events/Commands/CMD_Message.h>
#include <Windows/Window_Message.h>

namespace Szczur {
	CMD_Message::CMD_Message(const char* msg, float time) :EventCommand("CMD_Message") {
		this->msg = sf::String(msg);
		this->time = time;
		runState = 0;
	}
	
	CMD_Message::CMD_Message(const wchar_t* msg, float time) :EventCommand("CMD_Message") {
		this->msg = sf::String(msg);
		this->time = time;
		runState = 0;
	}
	
	CMD_Message::CMD_Message(sf::String msg, float time) :EventCommand("CMD_Message") {
		this->msg = msg;
		this->time = time;
		runState = 0;
	}
	
	void CMD_Message::run(int& index) {
		if (runState == 0) {
			new Window_Message(this);
			runState = 1;
			index--;
			return;
		}
		if (runState == 1) {
			index--;
			return;
		}
		if (runState == 2) {
			runState = 0;
		}
	}
}
