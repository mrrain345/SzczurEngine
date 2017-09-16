#pragma once
#include <Szczur/Vector2.h>
#include <Szczur/Color.h>
#include <SFML/Graphics/Font.hpp>

namespace Szczur {
	class Window;
	
	class WindowContent {
	public:
		Color textColor;
		
		WindowContent(Window* window);
		
		void fill(Color color, unsigned char opacity = 255);
		void fillRect(Rect rect, Color color, unsigned char opacity = 255);
		
		void drawText(Vector2 position, const char* str, unsigned int fontSize = 18);
		void drawText(Vector2 position, const char* str, sf::Font& font, unsigned int fontSize = 18);
		void drawText(Vector2 position, const wchar_t* str, unsigned int fontSize = 18);
		void drawText(Vector2 position, const wchar_t* str, sf::Font& font, unsigned int fontSize = 18);
		float animation(float begin, float end, float(*func)(float), float state);
	
	private:
		Window* window;
	};
}
