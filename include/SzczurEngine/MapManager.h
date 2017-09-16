#pragma once
#include <Szczur/Types.h>
#include <SzczurEngine/Map.h>
#include <SzczurEngine/Player.h>

namespace Szczur {
	class MapManager {
	public:
		static Player* player;
		
		static void init();
		static Map* current();
		static void load(const char* name);
		
		static void draw();
		static bool isCollision(Vector2 pos);
		static bool isCollision(Rect rect);
		
		static void close();
	
	private:
		MapManager() {} //Static class
		static bool isInitialize;
		
		static Map* _current;
	};
}
