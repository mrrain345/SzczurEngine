#pragma once
#include <SzczurEngine/Events/Event.h>
#include <SzczurEngine/Events/EventPage.h>
#include <SzczurEngine/Events/EventCommand.h>
#include <list>

namespace Szczur {
	class EventConditions;	
	
	class EventPage {
	public:
		int nextCmd;
		bool isRunning;
	
		EventPage();
		EventPage(EventCommand** commands, int cmd_count);
		EventPage(EventConditions* conditions, EventCommand** commands, int cmd_count);
		EventPage(std::list<EventCommand*> commands);
		EventPage(EventConditions* conditions, std::list<EventCommand*> commands);
		
		bool checkConditions(Event::StartMode mode);
		int runEvent();
		
	private:
		EventConditions* conditions;
		EventCommand** commands;
		int cmd_count;
	};
}
