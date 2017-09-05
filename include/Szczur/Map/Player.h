#pragma once
#include <Szczur/System/Time.h>
#include <Szczur/System/Vector2.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

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
		void Move(int dir, Vector2 vector);
		bool CanMove(Vector2 vector);
		
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
