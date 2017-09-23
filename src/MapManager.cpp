#include <Szczur/Types.h>
#include <SzczurEngine/MapManager.h>
#include <SzczurEngine/Map.h>

namespace Szczur {
	Map* MapManager::_current;
	bool MapManager::isInitialize = false;
	Player* MapManager::player;
	
	void MapManager::init() {
		if (isInitialize) return;
		else isInitialize = true;
		_current = new Map("map01");
		player = new Player();
	}
	
	Map* MapManager::current() {
		return _current;
	}
	
	void MapManager::load(const char* name) {
		_current = new Map(name);
	}
	
	void MapManager::draw() {
		_current->drawBack();
		player->draw();
		_current->drawFront();
	}
	
	bool MapManager::isCollision(Vector2 pos) {
		return _current->isCollision(pos);
	}
	
	bool MapManager::isCollision(Rect rect) {
		return _current->isCollision(rect);
	}
	
	void MapManager::close() {
		delete player;
		delete _current;
		_current = 0;
	}
}
