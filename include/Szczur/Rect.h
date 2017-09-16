#pragma once
#include <Szczur/Vector2.h>
#include <SFML/Graphics/Rect.hpp>

namespace Szczur {
	class Rect {
	public:
		int x;
		int y;
		int width;
		int height;
		
		Rect();
		Rect(int width, int height);
		Rect(int x, int y, int width, int height);
		Rect(Vector2 position, Vector2 size);
		Rect(sf::IntRect rect);
		
		void set(int x, int y, int width, int height);
		
		bool contains(int x, int y);
		bool contains(Vector2 point);
		bool contains(Rect rect);
		
		static Rect commonPart(Rect rect1, Rect rect2);
		
		operator sf::IntRect();
	};
}
