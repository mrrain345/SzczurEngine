#include <Szczur/System.h>
#include <Szczur/Map/Map.h>
#include <string>

namespace Szczur {
	Map::Map(const char* name) {
		sf::String str(name);
		backimage = Content::Sprite(std::string("Maps/" + str + "/backimage.png").c_str());
		frontimage = Content::Sprite(std::string("Maps/" + str + "/frontimage.png").c_str());
		collisions = Content::Image(std::string("Maps/" + str + "/collisions.png").c_str());
		
		OffsetRecalc();
	}
	
	void Map::OffsetRecalc() {
		sf::Vector2u size = backimage.getTexture()->getSize();
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
		sf::Vector2u size = collisions->getSize();
		if (pos.x >= size.x || pos.y >= size.y) return true;

		Color col = collisions->getPixel((unsigned)pos.x, (unsigned)pos.y);
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
	
	Map::~Map() {
		Content::Close(backimage);
		Content::Close(frontimage);
		Content::Close(collisions);
	}
}
