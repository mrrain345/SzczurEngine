#pragma once
#include <Szczur/Events/Event.h>
#include <list>

namespace Szczur {
	class EventConditions {
	public:
		struct Switch {
			int id;
			bool value;
		};
		
		Event::StartMode startMode;
		std::list<Switch> switches;
		
		EventConditions();
		EventConditions(Event::StartMode startMode);
		EventConditions(Event::StartMode startMode, int switchId, bool switchVal = true);
		EventConditions(Event::StartMode startMode, std::list<Switch> switches);
		
		void addSwitch(int switchId, bool switchVal = true);
		
		bool check(Event::StartMode startMode);
	};
}
