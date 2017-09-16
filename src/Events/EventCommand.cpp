#include <SzczurEngine/Events/EventCommand.h>

namespace Szczur {
	EventCommand::EventCommand(const char* command) {
		this->command = command;
	}
	
	EventCommand::EventCommand(std::string command) {
		this->command = command;
	}
}
