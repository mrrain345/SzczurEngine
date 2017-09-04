#pragma once
#include <SFML/Graphics.hpp>

namespace Szczur {
	class Map {
	private:
		sf::Texture tex_backimage;
		sf::Texture tex_frontimage;
		sf::Image collisions;
		
		sf::Sprite backimage;
		sf::Sprite frontimage;
		
		sf::Vector2f offset;
		
	public:
		Map(const char* name);
		void OffsetRecal();
		void DrawBack();
		void DrawFront();
		bool IsCollision(sf::Vector2f pos);
		bool IsCollision(sf::IntRect rect);
	};
}
