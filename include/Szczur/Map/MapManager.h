#pragma once
#include <Szczur/System/Vector2.h>
#include <Szczur/System/Rect.h>
#include <Szczur/Map/Map.h>
#include <Szczur/Map/Player.h>

namespace Szczur {
	class MapManager {
	private:
		MapManager() {} //Static class
		static bool isInitialize;
		
	public:
		static Map* current;
		static Player* player;
		
		static void Init();
		static Map* Current();
		static void Load(const char* name);
		
		static void Draw();
		static bool IsCollision(Vector2 pos);
		static bool IsCollision(Rect rect);
		
		static void Close();
	};
}
