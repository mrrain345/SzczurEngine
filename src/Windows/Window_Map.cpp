#include <Szczur/Map/MapManager.h>
#include <Szczur/Events/Event.h>
#include <Windows/Window_Map.h>
#include <Windows/Window_Menu.h>
#include <iostream>

namespace Szczur {
	Window_Map::Window_Map() {
		activeEvent = NULL;
	
		MapManager::Init();
		SetActive();
	}
	
	void Window_Map::Refresh() {
		MapManager::Draw();
	}
	
	void Window_Map::Update() {
		if (activeEvent) {
			if (!activeEvent->EventTrigger(Event::START_ButtonPress)) {
				activeEvent = NULL;
				MapManager::player->eventLock = false;
			}
		}
	}
	
	void Window_Map::OnKeyPress(Input::Key key) {
		if (activeEvent) return;
		
		if (key == Input::KEY_Escape) new Window_Menu();
		if (key == Input::KEY_Space) {
			for (auto object: MapManager::current->objects) {
				if (Vector2::Distance(MapManager::player->GetPosition(), object->position) <= 25) {
					if (object->EventTrigger(Event::START_ButtonPress)) {
						activeEvent = object->event;
						MapManager::player->eventLock = true;
						return;
					}
				}
			}
		}
	}
	
	void Window_Map::OnLostActive() {
		MapManager::player->lockMove = true;
	}
	
	void Window_Map::OnGainActive() {
		MapManager::player->lockMove = false;
	}
	
	void Window_Map::OnClosed() {
		MapManager::Close();
	}
}
