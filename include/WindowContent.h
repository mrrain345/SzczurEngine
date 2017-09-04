#pragma once
#include <SFML/Graphics.hpp>

namespace Szczur {
	class Window;
	
	class WindowContent {
	private:
		Window* window;
		
	public:
		sf::Color textColor;
		
		WindowContent(Window* window);
		
		void Fill(sf::Color color, unsigned char opacity = 255);
		void FillRect(sf::IntRect rect, sf::Color color, unsigned char opacity = 255);
		void DrawText(sf::Vector2f position, const char* str, unsigned int fontSize = 18);
		void DrawText(sf::Vector2f position, const char* str, sf::Font font, unsigned int fontSize = 18);
		void DrawText(sf::Vector2f position, sf::String str, unsigned int fontSize = 18);
		void DrawText(sf::Vector2f position, sf::String str, sf::Font font, unsigned int fontSize = 18);
	};
}
