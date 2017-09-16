#define SZCZUR_CORE
#include <SzczurEngine/GameObject.h>
#include <SFML/Graphics/Sprite.hpp>

namespace Szczur {
	GameObject::GameObject() {
		position.set(0, 0);
		collider.set(-10, -10, 20, 20);
		isTrigger = false;
		event = NULL;
	}
	
	GameObject::GameObject(Vector2 position) {
		this->position = position;
		collider.set(-10, -10, 20, 20);
		isTrigger = false;
		event = NULL;
	}
	
	GameObject::GameObject(float x, float y) {
		position.set(x, y);
		collider.set(-10, -10, 20, 20);
		isTrigger = false;
		event = NULL;
	}
	
	bool GameObject::eventTrigger(Event::StartMode mode) {
		if (event) return event->eventTrigger(mode);
		return false;
	}
	
	GameObject::~GameObject() {
		if (event) delete event;
	}
}
