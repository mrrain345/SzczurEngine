#pragma once
#include <Szczur/Time.h>
#include <Szczur/Vector2.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace Szczur {
	class Player : TimeEvents {
	public:
		sf::Sprite sprite;
		bool lockMove;
		bool eventLock;
		
		Player();
		void draw();
		Vector2 position();
		
		void update();
		
		~Player();
		
	private:
		float time;
		int colliderRadius;
		
		void setFrame(int face, int n);
		void setFace(int index);
		void setAnim(int index);
		void nextAnim();
		void updateAnim();
		void move(int dir, Vector2 vector);
		bool canMove(Vector2 vector);
		
		int frames;
		int directions;
		int width;
		int height;
	};
}
