#pragma once
#include <list>

namespace Szczur {
	class EventPage;
	
	class Event {	
	public:
		enum StartMode {
			START_NONE = 0,
			START_PRESS,
			START_TOUCH_PLAYER,
			START_TOUCH_EVENT,
			START_AUTOSTART,
			START_PARALLEL
		};
		
		std::list<EventPage> pages;
		
		Event();
		Event(EventPage page);
		Event(std::list<EventPage> pages);
		
		void addPage(EventPage page);
		bool eventTrigger(StartMode mode);
		
	private:
		EventPage* active;
		int nextCmd;
	};
}
