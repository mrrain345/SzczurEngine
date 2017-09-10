#include <Szczur/System/Content.h>
#include <iostream>

namespace Szczur {
	std::list<Content::ContentEntry<sf::Texture>*>	Content::textures;
	std::list<Content::ContentEntry<sf::Image>*>	Content::images;
	std::list<Content::ContentEntry<sf::Font>*>		Content::fonts;
	
	sf::Font* Content::defaultFont = 0;
	
	sf::Texture*	Content::Texture	(const char* name) { return Texture(std::string(name)); }
	sf::Image*		Content::Image		(const char* name) { return Image(std::string(name)); }
	sf::Font*		Content::Font		(const char* name) { return Font(std::string(name)); }
	sf::Sprite		Content::Sprite		(const char* name) { return Sprite(std::string(name)); }
	sf::Sprite		Content::Character	(const char* name) { return Character(std::string(name)); }
	
	sf::Texture* Content::Texture(std::string name) {
		for (auto entry: textures) {
			if (entry->path == name) {
				entry->count++;
				return &entry->resource;
			}
		}
		
		ContentEntry<sf::Texture>* entry = new ContentEntry<sf::Texture> {std::string(name), 1, sf::Texture()};
		if (!entry->resource.loadFromFile(name)) {
			delete entry;
			return NULL;
		}
		textures.push_back(entry);
		return &entry->resource;
	};

	sf::Image* Content::Image(std::string name) {
		for (auto entry: images) {
			if (entry->path == name) {
				entry->count++;
				return &entry->resource;
			}
		}
		
		ContentEntry<sf::Image>* entry = new ContentEntry<sf::Image> {std::string(name), 1, sf::Image()};
		if (!entry->resource.loadFromFile(name)) {
			delete entry;
			return NULL;
		}
		images.push_back(entry);
		return &entry->resource;
	}
	
	sf::Font* Content::Font(std::string name) {
		for (auto entry: fonts) {
			if (entry->path == name) {
				entry->count++;
				return &entry->resource;
			}
		}
		
		ContentEntry<sf::Font>* entry = new ContentEntry<sf::Font> {std::string(name), 1, sf::Font()};
		if (!entry->resource.loadFromFile(name)) {
			delete entry;
			return NULL;
		}
		fonts.push_back(entry);
		return &entry->resource;
	}
	
	sf::Sprite Content::Sprite(std::string name) {
		return sf::Sprite(*Texture(name));
	}

	sf::Sprite Content::Character(std::string name) {
		std::string path = "Graphics/Characters/" + std::string(name) + ".png";
		return sf::Sprite(*Texture(path.c_str()));
	}

	void Content::Close(const sf::Texture* texture) {
		for (auto entry: textures) {
			if (&entry->resource == texture) {
				entry->count--;
				if (entry->count == 0) textures.remove(entry);
				return;
			}
		}
		std::cout << "You're trying to close unopened texture!" << std::endl;
	}
	
	void Content::Close(const sf::Image* image) {
		for (auto entry: images) {
			if (&entry->resource == image) {
				entry->count--;
				if (entry->count == 0) images.remove(entry);
				return;
			}
		}
		std::cout << "You're trying to close unopened image!" << std::endl;
	}
	
	void Content::Close(const sf::Font* font) {
		for (auto entry: fonts) {
			if (&entry->resource == font) {
				entry->count--;
				if (entry->count == 0) fonts.remove(entry);
				return;
			}
		}
		std::cout << "You're trying to close unopened font!" << std::endl;
	}
	
	void Content::Close(const sf::Sprite& sprite) {
		Close(sprite.getTexture());
	}
	
	sf::Font& Content::DefaultFont() {
		if (defaultFont == 0) defaultFont = Font("Fonts/OpenSans-Regular.ttf");
		return *defaultFont;
	}
	
	void Content::DebugPrint() {
		if (textures.size() == 0 && images.size() == 0 && fonts.size() == 0) return;
		
		std::cout << "Cached Content:" << std::endl;
		
		if (textures.size()) {
			std::cout << " Textures(" << textures.size() << ")" << std::endl;
			for (auto entry: textures) std::cout << "  [" << entry->count << "] " << entry->path << std::endl;
		}
		
		if (images.size()) {
			std::cout << " Images(" << images.size() << ")" << std::endl;
			for (auto entry: images) std::cout << "  [" << entry->count << "] " << entry->path << std::endl;
		}
		
		if (fonts.size()) {
			std::cout << " Fonts(" << fonts.size() << ")" << std::endl;
			for (auto entry: fonts) std::cout << "  [" << entry->count << "] " << entry->path << std::endl;
		}
	}
}
