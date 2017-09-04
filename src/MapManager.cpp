#include <MapManager.h>

namespace Szczur {
	Map* MapManager::current;
	bool MapManager::isInitialize = false;
	
	void MapManager::Init() {
		if (isInitialize) return;
		else isInitialize = true;
		current = new Map("map01");
	}
	
	Map* MapManager::Current() {
		return current;
	}
	
	void MapManager::Load(const char* name) {
		current = new Map(name);
	}
	
	void MapManager::DrawBack() {
		current->DrawBack();
	}
	
	void MapManager::DrawFront() {
		current->DrawFront();
	}
	
	bool MapManager::IsCollision(sf::Vector2f pos) {
		return current->IsCollision(pos);
	}
	
	bool MapManager::IsCollision(sf::IntRect rect) {
		return current->IsCollision(rect);
	}
}
