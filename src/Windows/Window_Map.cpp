#include <SzczurEngine/MapManager.h>
#include <SzczurEngine/Events/Event.h>
#include <Szczur/Module.h>
#include <Windows/Window_Map.h>
#include <Windows/Window_Menu.h>
#include <iostream>

namespace Szczur {
	Window_Map::Window_Map() {
		activeEvent = NULL;
	
		MapManager::init();
		setActive();
	}
	
	void Window_Map::refresh() {
		MapManager::draw();
	}
	
	void Window_Map::update() {
		if (activeEvent) {
			if (!activeEvent->eventTrigger(Event::START_PRESS)) {
				activeEvent = NULL;
				MapManager::player->eventLock = false;
			}
		}
	}
	
	void Window_Map::onKeyPress(Input::Key key) {
		if (activeEvent) return;
		
		if (key == Input::KEY_ESCAPE) Module::send("system", "menu", "window-show", NULL);
		if (key == Input::KEY_SPACE) {
			for (auto object: MapManager::current()->objects) {
				if (Vector2::distance(MapManager::player->position(), object->position) <= 25) {
					if (object->eventTrigger(Event::START_PRESS)) {
						activeEvent = object->event;
						MapManager::player->eventLock = true;
						return;
					}
				}
			}
		}
	}
	
	void Window_Map::onLostActive() {
		MapManager::player->lockMove = true;
	}
	
	void Window_Map::onGainActive() {
		MapManager::player->lockMove = false;
	}
	
	void Window_Map::onClosed() {
		MapManager::close();
	}
}
