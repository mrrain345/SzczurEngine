#pragma once
#include <Szczur/System/Vector2.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace Szczur {
	class Map {
	private:
		sf::Texture tex_backimage;
		sf::Texture tex_frontimage;
		sf::Image collisions;
		
		sf::Sprite backimage;
		sf::Sprite frontimage;
		
		Vector2 offset;
		
	public:
		Map(const char* name);
		void OffsetRecal();
		void DrawBack();
		void DrawFront();
		bool IsCollision(Vector2 pos);
		bool IsCollision(Rect rect);
	};
}
