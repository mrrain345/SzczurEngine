#pragma once
#include <SFML/Graphics.hpp>
#include <Time.h>

namespace Szczur {
	class Player : TimeEvents {
	private:
		float time;
		int colliderRadius;
		
		void SetFrame(int face, int n);
		void SetFace(int index);
		void SetAnim(int index);
		void NextAnim();
		void UpdateAnim();
		void Move(int dir, sf::Vector2f vector);
		
		int frames;
		int directions;
		int width;
		int height;
		
	public:
		sf::Texture texture; //TODO: ContentManager
		sf::Sprite sprite;
		bool lockMove;
		
		Player();
		void Draw();
		
		void Update();
	};
}
