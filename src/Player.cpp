#include <Player.h>
#include <Time.h>
#include <Game.h>
#include <MapManager.h>
#include <Input.h>
#include <iostream>

namespace Szczur {
	Player::Player() {
		texture.loadFromFile("Graphics/Characters/001-Fighter01.png");
		frames = 4;
		directions = 4;
		
		width = texture.getSize().x / frames;
		height = texture.getSize().y / directions;
		
		sprite.setTexture(texture);
		sprite.setOrigin(width / 2, height - 10);
		sprite.setPosition(20*32 + 16, 14*32 + 16);
		
		time = 0;
		colliderRadius = 10;
		lockMove = false;
		
		SetFrame(0, 0);
		Time::Register(this);
	}
	
	void Player::SetFrame(int face, int n) {
		sf::IntRect rect(n * width, face * height, width, height);
		if (rect == sprite.getTextureRect()) return;
		sprite.setTextureRect(sf::IntRect(rect));
		Game::Refresh();
	}
	
	void Player::SetFace(int index) {
		sf::IntRect rect(sprite.getTextureRect().left, index * height, width, height);
		if (rect == sprite.getTextureRect()) return;
		sprite.setTextureRect(rect);
		Game::Refresh();
	}
	
	void Player::SetAnim(int index) {
		sf::IntRect rect(index * width, sprite.getTextureRect().top, width, height);
		if (rect == sprite.getTextureRect()) return;
		sprite.setTextureRect(rect);
		Game::Refresh();
	}
	
	void Player::NextAnim() {
		int index = sprite.getTextureRect().left / width;
		index = (index+1) % frames;
		SetAnim(index);
	}
	
	void Player::UpdateAnim() {
		time += Time::DeltaTime();
		if (time >= 0.2f) {
			time -= 0.2f;
			NextAnim();
		}
	}
	
	void Player::Move(int dir, sf::Vector2f vector) {
		float distance = 4 * Time::DeltaTime();
		SetFace(dir);
		
		vector *= distance;
		int x = (int)(sprite.getPosition().x + vector.x) - colliderRadius;
		int y = (int)(sprite.getPosition().y + vector.y) - colliderRadius;
		sf::IntRect rect = sf::IntRect(x, y, colliderRadius * 2, colliderRadius * 2);
		if (MapManager::IsCollision(rect)) {
			SetAnim(0);
			return;
		}
		
		sprite.setPosition(sprite.getPosition().x + vector.x, sprite.getPosition().y + vector.y);
		Game::Refresh();
	}
	
	
	void Player::Draw() {
		Game::Draw(sprite);
	}
	
	void Player::Update() {
		if (lockMove) return;
		
		const float s1 = 32.0f;
		const float s2 = 22.627416998f;
		
		bool key[4];
		key[0] = Input::IsKeyPressed(Input::KEY_Down);
		key[1] = Input::IsKeyPressed(Input::KEY_Left);
		key[2] = Input::IsKeyPressed(Input::KEY_Right);
		key[3] = Input::IsKeyPressed(Input::KEY_Up);
		
		if		(key[0] && key[1]) Move(1, sf::Vector2f(-s2,  s2));
		else if (key[0] && key[2]) Move(2, sf::Vector2f( s2,  s2));
		else if (key[1] && key[3]) Move(1, sf::Vector2f(-s2, -s2));
		else if (key[2] && key[3]) Move(2, sf::Vector2f( s2, -s2));
		else if (key[0])           Move(0, sf::Vector2f(  0,  s1));
		else if (key[1])           Move(1, sf::Vector2f(-s1,   0));
		else if (key[2])           Move(2, sf::Vector2f( s1,   0));
		else if (key[3])           Move(3, sf::Vector2f(  0, -s1));
		else                           { SetAnim(0); return; }
		
		UpdateAnim();
	}
	
}
