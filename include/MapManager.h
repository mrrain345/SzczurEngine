#pragma once
#include <Map.h>
#include <SFML/Graphics.hpp>

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
		static bool IsCollision(sf::Vector2f pos);
		static bool IsCollision(sf::IntRect rect);
	};
}
