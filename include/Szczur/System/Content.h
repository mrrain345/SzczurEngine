#pragma once
#include <SFML/Graphics.hpp>
#include <Szczur/Map/Map.h>
#include <string>
#include <list>

namespace Szczur {
	class Content {
	private:
		template<typename T>
		struct ContentEntry {
			std::string path;
			int count;
			T resource;
		};
		
		static std::list<ContentEntry<sf::Texture>*>	textures;
		static std::list<ContentEntry<sf::Image>*>		images;
		static std::list<ContentEntry<sf::Font>*>		fonts;
		
		static sf::Font* defaultFont;
		
	public:
		static sf::Texture*	Texture		(const char* name);
		static sf::Image*	Image		(const char* name);
		static sf::Font*	Font		(const char* name);
		static sf::Sprite	Sprite		(const char* name);
		static sf::Sprite	Character	(const char* name);
		
		static sf::Texture*	Texture		(std::string name);
		static sf::Image*	Image		(std::string name);
		static sf::Font*	Font		(std::string name);
		static sf::Sprite	Sprite		(std::string name);
		static sf::Sprite	Character	(std::string name);
		
		static void Close(const sf::Texture* texture);
		static void Close(const sf::Image* image);
		static void Close(const sf::Font* font);
		static void Close(const sf::Sprite& sprite);
		
		static sf::Font& DefaultFont();
		
		static void DebugPrint();
	};
}
