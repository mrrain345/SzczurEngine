#include <Szczur/Events/EventPage.h>
#include <Szczur/Events/EventConditions.h>
#include <iostream>

namespace Szczur {
	EventPage::EventPage() {
		this->conditions = NULL;
		this->commands = NULL;
		this->cmd_count = 0;
		nextCmd = 0;
	}
	
	EventPage::EventPage(EventCommand** commands, int cmd_count) {
		this->conditions = NULL;
		this->commands = commands;
		this->cmd_count = cmd_count;
		nextCmd = 0;
	}
	
	EventPage::EventPage(EventConditions* conditions, EventCommand** commands, int cmd_count) {
		this->conditions = conditions;
		this->commands = commands;
		this->cmd_count = cmd_count;
		nextCmd = 0;
	}
	
	EventPage::EventPage(std::list<EventCommand*> commands) {
		this->conditions = NULL;
		this->cmd_count = commands.size();
		this->commands = new EventCommand*[cmd_count];
		int i = 0;
		for (auto command: commands) this->commands[i++] = command;
		nextCmd = 0;
	}
	
	EventPage::EventPage(EventConditions* conditions, std::list<EventCommand*> commands) {
		this->conditions = conditions;
		this->cmd_count = commands.size();
		this->commands = new EventCommand*[cmd_count];
		int i = 0;
		for (auto command: commands) this->commands[i++] = command;
		nextCmd = 0;
	}
	
	bool EventPage::checkConditions() {
		if (conditions == NULL) return true;
		return conditions->check();
	}
	
	int EventPage::runEvent() {
		int i = nextCmd;
		commands[i]->run(++nextCmd);
		if (nextCmd < 0 || nextCmd >= cmd_count) {
			nextCmd = 0;
			return -1;
		}
		return nextCmd;
	}
}
