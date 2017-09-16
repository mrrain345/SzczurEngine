#pragma once
#include <Szczur/Types.h>
#include <SzczurEngine/GameObject.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <list>

namespace Szczur {
	class Map {
	public:
		std::list<GameObject*> objects;
	
		Map(const char* name);
		void offsetRecalc();
		void drawBack();
		void drawFront();
		bool isCollision(Vector2 pos);
		bool isCollision(Rect rect);
		
		~Map();
		
	private:
		sf::Sprite backimage;
		sf::Sprite frontimage;
		sf::Image* collisions;
		
		Vector2 offset;
	};
}
