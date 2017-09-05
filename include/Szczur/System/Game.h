#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Szczur {
	class Game {
	private:
		Game() {} //Static class
		
		static bool refreshFlag;
		static int width;
		static int height;
		static bool isInitialize;
		
	public:
		static void Init(const char* title, int width, int height);
		
		static sf::RenderWindow window;
		
		static void Refresh();
		static void Loop();
		static void Draw(const sf::Drawable& draw);
		static void Close();
		
		static int Width();
		static int Height();
		
		static sf::Font defaultFont;
	};
}
