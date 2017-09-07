#pragma once
#include <Szczur/System/Vector2.h>
#include <Szczur/System/Rect.h>
#include <Szczur/Map/Map.h>

namespace Szczur {
	class MapManager {
	private:
		MapManager() {} //Static class
		
		static Map* current;
		static bool isInitialize;
		
	public:
		static void Init();
		static Map* Current();
		static void Load(const char* name);
		
		static void DrawBack();
		static void DrawFront();
		static bool IsCollision(Vector2 pos);
		static bool IsCollision(Rect rect);
		
		static void Close();
	};
}
