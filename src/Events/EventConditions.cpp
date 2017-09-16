#include <SzczurEngine/Events/EventConditions.h>
#include <SzczurEngine/Game.h>

namespace Szczur {		
	EventConditions::EventConditions() {
		startMode = Event::START_PRESS;
	}
	
	EventConditions::EventConditions(Event::StartMode startMode) {
		this->startMode = startMode;
	}
	
	EventConditions::EventConditions(Event::StartMode startMode, int switchId, bool switchVal) {
		this->startMode = startMode;
		switches.push_back(Switch {switchId, switchVal});
	}
	
	EventConditions::EventConditions(Event::StartMode startMode, std::list<Switch> switches) {
		this->startMode = startMode;
		switches = switches;
	}
	
	void EventConditions::addSwitch(int switchId, bool switchVal) {
		switches.push_back(Switch {switchId, switchVal});
	}
	
	bool EventConditions::check(Event::StartMode startMode) {
		if (this->startMode != startMode) return false;
		if (switches.size() == 0) return true;
		
		for (auto entry: switches) if (Game::switches[entry.id] != entry.value) return false;
		return true;
	}
}
