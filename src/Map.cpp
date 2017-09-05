#include <Szczur/System.h>
#include <Szczur/Map/Map.h>

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
		offset = Vector2(x, y);
		backimage.setPosition(offset);
		frontimage.setPosition(offset);
	}
	
	void Map::DrawBack() {
		Game::Draw(backimage);
	}
	
	void Map::DrawFront() {
		Game::Draw(frontimage);
	}
	
	bool Map::IsCollision(Vector2 pos) {
		pos -= offset;
		if (pos.x < 0 || pos.y < 0) return true;
		sf::Vector2u size = collisions.getSize();
		if (pos.x >= size.x || pos.y >= size.y) return true;

		Color col = collisions.getPixel((unsigned)pos.x, (unsigned)pos.y);
		return ((col.r * col.g * col.b) / 3) >= 128;
	}
	
	bool Map::IsCollision(Rect rect) {
		for(int y = rect.y; y < rect.y + rect.height; y++) {
			for(int x = rect.x; x < rect.x + rect.width; x++) {
				bool col = IsCollision(Vector2(x, y));
				if (col) return true;
			}
		}
		return false;
	}
}
