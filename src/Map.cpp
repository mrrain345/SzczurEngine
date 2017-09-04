#include <Map.h>
#include <Game.h>

namespace Szczur {
	Map::Map(const char* name) {
		sf::String str(name);
		tex_backimage.loadFromFile("Maps/" + str + "/backimage.png");
		tex_frontimage.loadFromFile("Maps/" + str + "/frontimage.png");
		collisions.loadFromFile("Maps/" + str + "/collisions.png");
		
		backimage.setTexture(tex_backimage);
		frontimage.setTexture(tex_frontimage);
		
		OffsetRecal();
	}
	
	void Map::OffsetRecal() {
		sf::Vector2u size = tex_backimage.getSize();
		int x = (Game::Width() - (int)size.x) / 2;
		int y = (Game::Height() - (int)size.y) / 2;
		offset = sf::Vector2f(x, y);
		backimage.setPosition(offset);
		frontimage.setPosition(offset);
	}
	
	void Map::DrawBack() {
		Game::Draw(backimage);
	}
	
	void Map::DrawFront() {
		Game::Draw(frontimage);
	}
	
	bool Map::IsCollision(sf::Vector2f pos) {
		pos -= offset;
		if (pos.x < 0 || pos.y < 0) return true;
		sf::Vector2u size = collisions.getSize();
		if (pos.x >= size.x || pos.y >= size.y) return true;

		sf::Color col = collisions.getPixel((unsigned)pos.x, (unsigned)pos.y);
		return ((col.r * col.g * col.b) / 3) >= 128;
	}
	
	bool Map::IsCollision(sf::IntRect rect) {
		for(int y = rect.top; y < rect.top + rect.height; y++) {
			for(int x = rect.left; x < rect.left + rect.width; x++) {
				bool col = IsCollision(sf::Vector2f(x, y));
				if (col) return true;
			}
		}
		return false;
	}
}
