#include <Szczur/System.h>
#include <Szczur/Map.h>

namespace Szczur {
	Map* MapManager::current;
	bool MapManager::isInitialize = false;
	Player* MapManager::player;
	
	void MapManager::Init() {
		if (isInitialize) return;
		else isInitialize = true;
		current = new Map("map01");
		player = new Player();
	}
	
	Map* MapManager::Current() {
		return current;
	}
	
	void MapManager::Load(const char* name) {
		current = new Map(name);
	}
	
	void MapManager::Draw() {
		current->DrawBack();
		player->Draw();
		current->DrawFront();
		
		
	}
	
	bool MapManager::IsCollision(Vector2 pos) {
		return current->IsCollision(pos);
	}
	
	bool MapManager::IsCollision(Rect rect) {
		return current->IsCollision(rect);
	}
	
	void MapManager::Close() {
		delete player;
		delete current;
		current = 0;
	}
}
