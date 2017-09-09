#include <Szczur/System.h>
#include <Szczur/Map.h>
#include <iostream>

namespace Szczur {
	Player::Player() {
		sprite = Content::Character("Fighter01-move");
		frames = 4;
		directions = 4;
		
		width = sprite.getTexture()->getSize().x / frames;
		height = sprite.getTexture()->getSize().y / directions;
		
		sprite.setOrigin(width / 2, height - 10);
		sprite.setPosition(20*32 + 16, 14*32 + 16);
		
		time = 0;
		colliderRadius = 10;
		lockMove = false;
		eventLock = false;
		
		SetFrame(0, 0);
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
	
	bool Player::CanMove(Vector2 vector) {
		int x = (int)(sprite.getPosition().x + vector.x) - colliderRadius;
		int y = (int)(sprite.getPosition().y + vector.y) - colliderRadius;
		sf::IntRect rect = sf::IntRect(x, y, colliderRadius * 2, colliderRadius * 2);
		return !MapManager::IsCollision(rect);
	}
	
	void Player::Move(int dir, Vector2 vector) {
		float distance = 4 * Time::DeltaTime();
		SetFace(dir);
		
		vector *= distance;
		if (!CanMove(vector)) {
			SetAnim(0);
			return;
		}
		
		sprite.setPosition(sprite.getPosition().x + vector.x, sprite.getPosition().y + vector.y);
		Game::Refresh();
	}
	
	
	void Player::Draw() {
		Game::Draw(sprite);
	}
	
	Vector2 Player::GetPosition() {
		return sprite.getPosition();
	}
	
	void Player::Update() {
		//std::cout << "Player pos: " << sprite.getPosition().x << "x" << sprite.getPosition().y << std::endl;
		if (lockMove || eventLock) return;
		float distance = 4 * Time::DeltaTime();
		
		const float s1 = 32.0f;
		const float s2 = 22.627416998f;
		
		bool key[4];
		key[0] = Input::IsKeyPressed(Input::KEY_Down);
		key[1] = Input::IsKeyPressed(Input::KEY_Left);
		key[2] = Input::IsKeyPressed(Input::KEY_Right);
		key[3] = Input::IsKeyPressed(Input::KEY_Up);
		
		if		(key[0] && key[1] && CanMove(Vector2(-s2,  s2)*distance)) Move(1, Vector2(-s2,  s2));
		else if (key[0] && key[2] && CanMove(Vector2( s2,  s2)*distance)) Move(2, Vector2( s2,  s2));
		else if (key[1] && key[3] && CanMove(Vector2(-s2, -s2)*distance)) Move(1, Vector2(-s2, -s2));
		else if (key[2] && key[3] && CanMove(Vector2( s2, -s2)*distance)) Move(2, Vector2( s2, -s2));
		else if (key[0]           && CanMove(Vector2(  0,  s1)*distance)) Move(0, Vector2(  0,  s1));
		else if (key[1]           && CanMove(Vector2(-s1,   0)*distance)) Move(1, Vector2(-s1,   0));
		else if (key[2]           && CanMove(Vector2( s1,   0)*distance)) Move(2, Vector2( s1,   0));
		else if (key[3]           && CanMove(Vector2(  0, -s1)*distance)) Move(3, Vector2(  0, -s1));
		else { SetAnim(0); return; }
		
		UpdateAnim();
	}
	
	Player::~Player() {
		Content::Close(sprite);
	}
}
