#pragma once
#include <Szczur/System/Vector2.h>
#include <Szczur/System/Rect.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace Szczur {
	class Map {
	private:
		sf::Sprite backimage;
		sf::Sprite frontimage;
		sf::Image* collisions;
		
		Vector2 offset;
		
	public:
		Map(const char* name);
		void OffsetRecalc();
		void DrawBack();
		void DrawFront();
		bool IsCollision(Vector2 pos);
		bool IsCollision(Rect rect);
		
		~Map();
	};
}
