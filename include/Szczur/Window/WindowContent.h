#pragma once
#include <Szczur/System.h>

#include <SFML/System/String.hpp>

namespace Szczur {
	class Window;
	
	class WindowContent {
	private:
		Window* window;
		
	public:
		Color textColor;
		
		WindowContent(Window* window);
		
		void Fill(Color color, unsigned char opacity = 255);
		void FillRect(Rect rect, Color color, unsigned char opacity = 255);
		void DrawText(Vector2 position, const char* str, unsigned int fontSize = 18);
		void DrawText(Vector2 position, const char* str, sf::Font font, unsigned int fontSize = 18);
		void DrawText(Vector2 position, sf::String str, unsigned int fontSize = 18);
		void DrawText(Vector2 position, sf::String str, sf::Font font, unsigned int fontSize = 18);
	};
}
