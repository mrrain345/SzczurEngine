#pragma once
#include <Szczur/Events/Event.h>
#include <Szczur/Events/EventPage.h>
#include <Szczur/Events/EventCommand.h>
#include <list>

namespace Szczur {
	class EventConditions;	
	
	class EventPage {
	private:
		EventConditions* conditions;
		EventCommand** commands;
		int cmd_count;
		
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
	};
}
