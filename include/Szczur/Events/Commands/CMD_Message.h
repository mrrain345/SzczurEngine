#pragma once
#include <Szczur/Events/EventCommand.h>

namespace Szczur {
	class CMD_Message :public EventCommand {
	public:
		std::string msg;
		float time;
		int runState;
		
		CMD_Message(const char* msg, float time = 1);
		CMD_Message(std::string msg, float time = 1);
		
		void run(int& index);
	};
}
