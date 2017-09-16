#pragma once
#include <string>

namespace Szczur {
	class EventCommand {
	public:
		std::string command;
		
		EventCommand(const char* command);
		EventCommand(std::string command);
		
		virtual void run(int& index) { run(); };
		virtual void run() {};
		virtual ~EventCommand() {}
	};
}
