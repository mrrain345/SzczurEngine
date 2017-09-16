#pragma once
#include <SzczurEngine/Events/EventCommand.h>
#include <SFML/System/String.hpp>

namespace Szczur {
	class CMD_SetSwitch :public EventCommand {
	public:
		int id;
		bool val;
		
		CMD_SetSwitch(int id, bool val = true);
		void run();
	};
}
