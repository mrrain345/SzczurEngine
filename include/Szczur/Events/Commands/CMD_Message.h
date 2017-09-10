#pragma once
#include <Szczur/Events/EventCommand.h>
#include <SFML/System/String.hpp>

namespace Szczur {
	class CMD_Message :public EventCommand {
	public:
		sf::String msg;
		float time;
		int runState;
		
		CMD_Message(const char* msg, float time = 1);
		CMD_Message(const wchar_t* msg, float time = 1);
		CMD_Message(sf::String msg, float time = 1);
		
		void run(int& index);
	};
}
