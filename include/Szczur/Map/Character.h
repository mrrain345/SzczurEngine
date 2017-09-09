#pragma once
#include <Szczur/System.h>
#include <Szczur/Map.h>
#include <SFML/Graphics/Sprite.hpp>

namespace Szczur {
	class Character :public GameObject {
	private:
		sf::Sprite idle_sprite;
		int idle_frames;
		Vector2 idle_size;
	
		sf::Sprite move_sprite;
		int move_frames;
		Vector2 move_size;
	
		int directions;
		bool isMoving;
		Vector2 velocity;
		int direction;
		int frame;
		
		void SetFrame(int frame);
		void RefreshDir();
		
	public:
		Character(float x, float y, const char* name);
		void Draw();
		~Character();
	};
}
