#include <Szczur/Map/GameObject.h>
#include <Szczur/System.h>
#include <SFML/Graphics/Sprite.hpp>

namespace Szczur {
	GameObject::GameObject() {
		position.Set(0, 0);
		collider.Set(-10, -10, 20, 20);
		isTrigger = false;
		event = NULL;
	}
	
	GameObject::GameObject(Vector2 position) {
		this->position = position;
		collider.Set(-10, -10, 20, 20);
		isTrigger = false;
		event = NULL;
	}
	
	GameObject::GameObject(float x, float y) {
		position.Set(x, y);
		collider.Set(-10, -10, 20, 20);
		isTrigger = false;
		event = NULL;
	}
	
	bool GameObject::EventTrigger(Event::StartMode mode) {
		if (event) return event->EventTrigger(mode);
		return false;
	}
	
	GameObject::~GameObject() {
		if (event) delete event;
	}
}
