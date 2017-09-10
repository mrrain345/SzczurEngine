#include <Szczur/Events/Event.h>
#include <Szczur/Events/EventPage.h>

namespace Szczur {
	Event::Event() {}
	
	Event::Event(EventPage page) {
		this->pages.push_back(page);
		active = NULL;
		nextCmd = 0;
	}
	
	Event::Event(std::list<EventPage> pages) {
		this->pages = pages;
		active = NULL;
		nextCmd = 0;
	}
	
	void Event::AddPage(EventPage page) {
		pages.push_back(page);
	}
	
	bool Event::EventTrigger(StartMode mode) {
		if (pages.size() == 0) return false;
		
		if (active != NULL) {
			nextCmd = active->runEvent();
			if (nextCmd == -1) {
				active = NULL;
				nextCmd = 0;
				return false;
			}
			return true;
		}
		
		for (std::list<EventPage>::reverse_iterator page = pages.rbegin(); page != pages.rend(); page++) {
			if (page->checkConditions(mode)) {
				active = &(*page);
				nextCmd = 0;
				nextCmd = page->runEvent();
				return true;
			}
		}
		
		return false;
	}
}
