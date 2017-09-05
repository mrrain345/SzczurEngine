#pragma once
#include <Szczur/System/Vector2.h>

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
		
		void Set(int x, int y, int width, int height);
		
		bool Contains(int x, int y);
		bool Contains(Vector2 point);
		bool Contains(Rect rect);
		
		static Rect CommonPart(Rect rect1, Rect rect2);
		
		operator sf::IntRect();
	};
}
