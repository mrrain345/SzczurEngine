#include <Szczur/System.h>
#include <Szczur/Map.h>

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
	
	bool MapManager::IsCollision(Vector2 pos) {
		return current->IsCollision(pos);
	}
	
	bool MapManager::IsCollision(Rect rect) {
		return current->IsCollision(rect);
	}
	
	void MapManager::Close() {
		delete current;
		current = 0;
	}
}
