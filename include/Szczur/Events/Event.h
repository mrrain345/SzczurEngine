#pragma once
#include <list>

namespace Szczur {
	class EventPage;
	class Event {
	private:
		EventPage* active;
		int nextCmd;
		
	public:
		enum StartMode {
			START_None = 0,
			START_ButtonPress,
			START_TouchPlayer,
			START_TouchEvent,
			START_Autostart,
			START_Parallel
		};
		
		std::list<EventPage> pages;
		
		Event();
		Event(EventPage page);
		Event(std::list<EventPage> pages);
		
		void AddPage(EventPage page);
		bool EventTrigger(StartMode mode);
	};
}
