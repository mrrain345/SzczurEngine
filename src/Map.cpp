#define SZCZUR_CORE
#include <Szczur/Types.h>
#include <SzczurEngine/Map.h>
#include <SzczurEngine/Events/Event.h>
#include <SzczurEngine/Events/EventConditions.h>
#include <SzczurEngine/Events/Commands/CMD_Message.h>
#include <SzczurEngine/Events/Commands/CMD_SetSwitch.h>
#include <SzczurEngine/Content.h>
#include <SzczurEngine/GameObject.h>
#include <SzczurEngine/Game.h>
#include <SzczurEngine/MapManager.h>
#include <SzczurEngine/Character.h>
#include <string>

namespace Szczur {
	Map::Map(const char* name) {
		std::string str(name);
		backimage = Content::sprite("Maps/" + str + "/backimage.png");
		frontimage = Content::sprite("Maps/" + str + "/frontimage.png");
		collisions = Content::image("Maps/" + str + "/collisions.png");
		
		offsetRecalc();
		
		// DEBUG BEGIN
		std::list<EventCommand*> cmd1;
		cmd1.push_back(new CMD_Message("Hello World!"));
		cmd1.push_back(new CMD_Message(L"Jestem testowym eventem!\nPotrafie wypowiadać kilku linijkowe zdania\ni już obsluguję polskie znaki :)", 4));
		cmd1.push_back(new CMD_SetSwitch(0));
		
		std::list<EventCommand*> cmd2;
		cmd2.push_back(new CMD_Message("Witaj ponownie :)"));
		
		GameObject* go = new Character(345, 330, "Fighter02");
		go->event = new Event(EventPage(cmd1));
		go->event->addPage(EventPage(new EventConditions(Event::START_PRESS, 0, true), cmd2));
		
		objects.push_back(go);
		std::list<EventCommand*> cmd3;
		cmd3.push_back(new CMD_Message(L"Dzień dobry /)\nPozdrawiam stream!", 0.4f));
		
		
		GameObject* go2 = new Character(245, 330, "Fighter03");
		go2->event = new Event(EventPage(cmd3));
		
		objects.push_back(go2);
		// DEBUG END
	}
	
	void Map::offsetRecalc() {
		sf::Vector2u size = backimage.getTexture()->getSize();
		int x = (Game::width() - (int)size.x) / 2;
		int y = (Game::height() - (int)size.y) / 2;
		offset = Vector2(x, y);
		backimage.setPosition(offset);
		frontimage.setPosition(offset);
	}
	
	void Map::drawBack() {
		Game::draw(backimage);
		for (auto object: objects) if(object->position.y <= MapManager::player->sprite.getPosition().y) object->draw();
	}
	
	void Map::drawFront() {
		Game::draw(frontimage);
		for (auto object: objects) if(object->position.y > MapManager::player->sprite.getPosition().y) object->draw();
	}
	
	bool Map::isCollision(Vector2 pos) {
		pos -= offset;
		if (pos.x < 0 || pos.y < 0) return true;
		sf::Vector2u size = collisions->getSize();
		if (pos.x >= size.x || pos.y >= size.y) return true;

		Color col = collisions->getPixel((unsigned)pos.x, (unsigned)pos.y);
		if (col.gray() > 128) return true;
		for (auto object: objects) {
			if (object->isTrigger) continue;
			
			Rect rect = object->collider;
			rect.x += object->position.x;
			rect.y += object->position.y;
			if (rect.contains(pos)) return true;
		}
		
		return false;
	}
	
	bool Map::isCollision(Rect rect) {
		for(int y = rect.y; y < rect.y + rect.height; y++) {
			for(int x = rect.x; x < rect.x + rect.width; x++) {
				bool col = isCollision(Vector2(x, y));
				if (col) return true;
			}
		}
		return false;
	}
	
	Map::~Map() {
		for (auto object: objects) delete object;
		objects.clear();
		Content::close(backimage);
		Content::close(frontimage);
		Content::close(collisions);
	}
}
