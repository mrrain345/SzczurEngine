#pragma once
#include <Szczur/Types.h>
#include <SzczurEngine/Events/Event.h>
#include <SzczurEngine/Events/EventPage.h>
#include <SFML/Graphics/Sprite.hpp>

namespace Szczur {
	class GameObject {
	public:
		Vector2 position;
		Rect collider;
		bool isTrigger;
		Event* event;
		
		GameObject();
		GameObject(Vector2 position);
		GameObject(float x, float y);
		
		bool eventTrigger(Event::StartMode mode);
		
		virtual void draw() {}
		virtual ~GameObject();
		
		/*enum AnimOptions {
			None = 0x00,
			Animation = 0x01,
			ConstAnim = 0x02,
			MoveBlock = 0x04,
			GhostMode = 0x08,
			AlwaysOnTop = 0x10
		}

		enum MotionMode {
			None = 0,
			Random = 1,
			Follow = 2,
			Path = 3
		}*/
	};
}
