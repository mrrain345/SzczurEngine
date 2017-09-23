#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <list>

namespace Szczur {
	class Game {
		friend class Module;
		
	public:
		static bool switches[5000];
		
		static sf::RenderWindow window;
		static void init(const char* title, int width, int height);
		
		static int width();
		static int height();
		
		static void refresh();
		static void draw(const sf::Drawable& draw);
		static void close();
	
	private:
		Game() {} //Static class
		static void loop();
		
		static bool refreshFlag;
		static int _width;
		static int _height;
		static bool isInitialize;
		
		static void drawToolbar();
		static void drawInspector();
		static void drawGame();
	};
}
