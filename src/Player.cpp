#define SZCZUR_CORE
#include <SzczurEngine/Player.h>
#include <SzczurEngine/Game.h>
#include <SzczurEngine/Content.h>
#include <SzczurEngine/MapManager.h>
#include <Szczur/Types.h>
#include <Szczur/Input.h>
#include <SzczurEngine/Map.h>

namespace Szczur {
	Player::Player() {
		sprite = Content::character("Fighter01-move");
		frames = 4;
		directions = 4;
		
		width = sprite.getTexture()->getSize().x / frames;
		height = sprite.getTexture()->getSize().y / directions;
		
		sprite.setOrigin(width / 2.0f, height - 10.0f);
		sprite.setPosition(20*32 + 16, 14*32 + 16);
		
		time = 0;
		colliderRadius = 10;
		lockMove = false;
		eventLock = false;
		
		setFrame(0, 0);
	}
	
	void Player::setFrame(int face, int n) {
		sf::IntRect rect(n * width, face * height, width, height);
		if (rect == sprite.getTextureRect()) return;
		sprite.setTextureRect(sf::IntRect(rect));
		Game::refresh();
	}
	
	void Player::setFace(int index) {
		sf::IntRect rect(sprite.getTextureRect().left, index * height, width, height);
		if (rect == sprite.getTextureRect()) return;
		sprite.setTextureRect(rect);
		Game::refresh();
	}
	
	void Player::setAnim(int index) {
		sf::IntRect rect(index * width, sprite.getTextureRect().top, width, height);
		if (rect == sprite.getTextureRect()) return;
		sprite.setTextureRect(rect);
		Game::refresh();
	}
	
	void Player::nextAnim() {
		int index = sprite.getTextureRect().left / width;
		index = (index+1) % frames;
		setAnim(index);
	}
	
	void Player::updateAnim() {
		time += Time::deltaTime();
		if (time >= 0.2f) {
			time -= 0.2f;
			nextAnim();
		}
	}
	
	bool Player::canMove(Vector2 vector) {
		int x = (int)(sprite.getPosition().x + vector.x) - colliderRadius;
		int y = (int)(sprite.getPosition().y + vector.y) - colliderRadius;
		Rect rect(x, y, colliderRadius * 2, colliderRadius * 2);
		return !MapManager::isCollision(rect);
	}
	
	void Player::move(int dir, Vector2 vector) {
		float distance = 4 * Time::deltaTime();
		setFace(dir);
		
		vector *= distance;
		if (!canMove(vector)) {
			setAnim(0);
			return;
		}
		
		sprite.setPosition(sprite.getPosition().x + vector.x, sprite.getPosition().y + vector.y);
		Game::refresh();
	}
	
	
	void Player::draw() {
		Game::draw(sprite);
	}
	
	Vector2 Player::position() {
		return sprite.getPosition();
	}
	
	void Player::update() {
		if (lockMove || eventLock) return;
		float distance = 4 * Time::deltaTime();
		
		const float s1 = 32.0f;
		const float s2 = 22.627416998f;
		
		bool key[4];
		key[0] = Input::isKeyPressed(Input::KEY_DOWN);
		key[1] = Input::isKeyPressed(Input::KEY_LEFT);
		key[2] = Input::isKeyPressed(Input::KEY_RIGHT);
		key[3] = Input::isKeyPressed(Input::KEY_UP);
		
		if		(key[0] && key[1] && canMove(Vector2(-s2,  s2)*distance)) move(1, Vector2(-s2,  s2));
		else if (key[0] && key[2] && canMove(Vector2( s2,  s2)*distance)) move(2, Vector2( s2,  s2));
		else if (key[1] && key[3] && canMove(Vector2(-s2, -s2)*distance)) move(1, Vector2(-s2, -s2));
		else if (key[2] && key[3] && canMove(Vector2( s2, -s2)*distance)) move(2, Vector2( s2, -s2));
		else if (key[0]           && canMove(Vector2(  0,  s1)*distance)) move(0, Vector2(  0,  s1));
		else if (key[1]           && canMove(Vector2(-s1,   0)*distance)) move(1, Vector2(-s1,   0));
		else if (key[2]           && canMove(Vector2( s1,   0)*distance)) move(2, Vector2( s1,   0));
		else if (key[3]           && canMove(Vector2(  0, -s1)*distance)) move(3, Vector2(  0, -s1));
		else { setAnim(0); return; }
		
		updateAnim();
	}
	
	Player::~Player() {
		Content::close(sprite);
	}
}
