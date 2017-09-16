#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <list>

namespace Szczur {
	class Content {
	public:
		static sf::Texture*	texture		(const char* name);
		static sf::Image*	image		(const char* name);
		static sf::Font*	font		(const char* name);
		static sf::Sprite	sprite		(const char* name);
		static sf::Sprite	character	(const char* name);
		
		static sf::Texture*	texture		(std::string name);
		static sf::Image*	image		(std::string name);
		static sf::Font*	font		(std::string name);
		static sf::Sprite	sprite		(std::string name);
		static sf::Sprite	character	(std::string name);
		
		static void close(const sf::Texture* texture);
		static void close(const sf::Image* image);
		static void close(const sf::Font* font);
		static void close(const sf::Sprite& sprite);
		
		static sf::Font& defaultFont();
		
		static void debugPrint();
		
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
		
		static sf::Font* _defaultFont;
	};
}
