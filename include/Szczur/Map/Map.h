#pragma once
#include <Szczur/System/Vector2.h>
#include <Szczur/System/Rect.h>
#include <Szczur/Map/GameObject.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <list>

namespace Szczur {
	class Map {
	private:
		sf::Sprite backimage;
		sf::Sprite frontimage;
		sf::Image* collisions;
		
		Vector2 offset;
		
	public:
		std::list<GameObject*> objects;
	
		Map(const char* name);
		void OffsetRecalc();
		void DrawBack();
		void DrawFront();
		bool IsCollision(Vector2 pos);
		bool IsCollision(Rect rect);
		
		~Map();
	};
}
