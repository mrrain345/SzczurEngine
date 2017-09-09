#pragma once
#include <Szczur/System/Vector2.h>
#include <Szczur/System/Rect.h>
#include <Szczur/Events/Event.h>
#include <Szczur/Events/EventPage.h>
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
		
		bool EventTrigger(Event::StartMode mode);
		
		virtual void Draw() {}
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
