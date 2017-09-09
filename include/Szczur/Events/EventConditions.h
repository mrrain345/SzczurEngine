#pragma once
#include <Szczur/Events/Event.h>

namespace Szczur {
	class EventConditions {
	public:
		Event::StartMode startMode;
		bool check() {};
	};
}
