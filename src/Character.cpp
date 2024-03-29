#include <SzczurEngine/Game.h>
#include <SzczurEngine/Content.h>
#include <SzczurEngine/Character.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics.hpp>
#include <string>

namespace Szczur {
	void Character::setFrame(int frame) {}
	void Character::refreshDir() {}
	
	Character::Character(float x, float y, const char* name) :GameObject(x, y) {
		idle_sprite = Content::character(name);
		move_sprite = Content::character(name);
		idle_frames = 4;
		move_frames = 4;
		directions = 4;
		
		Vector2 size = idle_sprite.getTexture()->getSize();
		idle_size = Vector2(size.x/idle_frames, size.y/directions);
		
		size = move_sprite.getTexture()->getSize();
		move_size = Vector2(size.x/move_frames, size.y/directions);
		
		isMoving = false;
		velocity.set(0, 0);
		direction = 0;
		frame = 0;
		
		idle_sprite.setTextureRect(Rect(0, 0, idle_size.x, idle_size.y));
		move_sprite.setTextureRect(Rect(0, 0, move_size.x, move_size.y));
		
		idle_sprite.setPosition(x, y);
		move_sprite.setPosition(x, y);
		
		idle_sprite.setOrigin(idle_size.x/2, idle_size.y - collider.height/2);
		move_sprite.setOrigin(move_size.x/2, move_size.y - collider.height/2);
	}
	
	void Character::draw() {
		if(isMoving) Game::draw(move_sprite);
		else Game::draw(idle_sprite);
	}
	
	Character::~Character() {
		Content::close(idle_sprite);
		Content::close(move_sprite);
	}
}
