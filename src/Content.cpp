#define SZCZUR_CORE
#include <SzczurEngine/Content.h>
#include <iostream>

namespace Szczur {
	std::list<Content::ContentEntry<sf::Texture>*>	Content::textures;
	std::list<Content::ContentEntry<sf::Image>*>	Content::images;
	std::list<Content::ContentEntry<sf::Font>*>		Content::fonts;
	
	sf::Font* Content::_defaultFont = NULL;
	
	sf::Texture*	Content::texture	(const char* name) { return texture(std::string(name)); }
	sf::Image*		Content::image		(const char* name) { return image(std::string(name)); }
	sf::Font*		Content::font		(const char* name) { return font(std::string(name)); }
	sf::Sprite		Content::sprite		(const char* name) { return sprite(std::string(name)); }
	sf::Sprite		Content::character	(const char* name) { return character(std::string(name)); }
	
	sf::Texture* Content::texture(std::string name) {
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

	sf::Image* Content::image(std::string name) {
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
	
	sf::Font* Content::font(std::string name) {
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
	
	sf::Sprite Content::sprite(std::string name) {
		return sf::Sprite(*texture(name));
	}

	sf::Sprite Content::character(std::string name) {
		std::string path = "Graphics/Characters/" + std::string(name) + ".png";
		return sf::Sprite(*texture(path.c_str()));
	}

	void Content::close(const sf::Texture* texture) {
		for (auto entry: textures) {
			if (&entry->resource == texture) {
				entry->count--;
				if (entry->count == 0) textures.remove(entry);
				return;
			}
		}
		std::cout << "You're trying to close unopened texture!" << std::endl;
	}
	
	void Content::close(const sf::Image* image) {
		for (auto entry: images) {
			if (&entry->resource == image) {
				entry->count--;
				if (entry->count == 0) images.remove(entry);
				return;
			}
		}
		std::cout << "You're trying to close unopened image!" << std::endl;
	}
	
	void Content::close(const sf::Font* font) {
		for (auto entry: fonts) {
			if (&entry->resource == font) {
				entry->count--;
				if (entry->count == 0) fonts.remove(entry);
				return;
			}
		}
		std::cout << "You're trying to close unopened font!" << std::endl;
	}
	
	void Content::close(const sf::Sprite& sprite) {
		close(sprite.getTexture());
	}
	
	sf::Font& Content::defaultFont() {
		if (_defaultFont == 0) _defaultFont = font("Fonts/OpenSans-Regular.ttf");
		return *_defaultFont;
	}
	
	void Content::debugPrint() {
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
