#include <Szczur/System.h>
#include <Szczur/Map.h>
#include <Szczur/Events.h>
#include <Szczur/Events/EventConditions.h>
#include <Szczur/Events/Commands/CMD_Message.h>
#include <Szczur/Events/Commands/CMD_SetSwitch.h>
#include <string>

namespace Szczur {
	Map::Map(const char* name) {
		std::string str(name);
		backimage = Content::Sprite("Maps/" + str + "/backimage.png");
		frontimage = Content::Sprite("Maps/" + str + "/frontimage.png");
		collisions = Content::Image("Maps/" + str + "/collisions.png");
		
		OffsetRecalc();
		
		// DEBUG BEGIN
		std::list<EventCommand*> cmd1;
		cmd1.push_back(new CMD_Message("Hello World!"));
		cmd1.push_back(new CMD_Message(L"Jestem testowym eventem!\nPotrafie wypowiadać kilku linijkowe zdania\ni już obsluguję polskie znaki :)", 4));
		cmd1.push_back(new CMD_SetSwitch(0));
		
		std::list<EventCommand*> cmd2;
		cmd2.push_back(new CMD_Message("Witaj ponownie :)"));
		
		GameObject* go = new Character(345, 330, "Fighter02");
		go->event = new Event(EventPage(cmd1));
		go->event->AddPage(EventPage(new EventConditions(Event::START_ButtonPress, 0, true), cmd2));
		
		objects.push_back(go);
		std::list<EventCommand*> cmd3;
		cmd3.push_back(new CMD_Message(L"Dzień dobry /)\nPozdrawiam stream!", 0.4f));
		
		
		GameObject* go2 = new Character(245, 330, "Fighter03");
		go2->event = new Event(EventPage(cmd3));
		
		objects.push_back(go2);
		// DEBUG END
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
		for (auto object: objects) if(object->position.y <= MapManager::player->sprite.getPosition().y) object->Draw();
	}
	
	void Map::DrawFront() {
		Game::Draw(frontimage);
		for (auto object: objects) if(object->position.y > MapManager::player->sprite.getPosition().y) object->Draw();
	}
	
	bool Map::IsCollision(Vector2 pos) {
		pos -= offset;
		if (pos.x < 0 || pos.y < 0) return true;
		sf::Vector2u size = collisions->getSize();
		if (pos.x >= size.x || pos.y >= size.y) return true;

		Color col = collisions->getPixel((unsigned)pos.x, (unsigned)pos.y);
		if (col.ToGray() > 128) return true;
		for (auto object: objects) {
			if (object->isTrigger) continue;
			
			Rect rect = object->collider;
			rect.x += object->position.x;
			rect.y += object->position.y;
			if (rect.Contains(pos)) return true;
		}
		
		return false;
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
		for (auto object: objects) delete object;
		objects.clear();
		Content::Close(backimage);
		Content::Close(frontimage);
		Content::Close(collisions);
	}
}
