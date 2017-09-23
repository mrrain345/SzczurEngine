#pragma once
#include <SFML/System/Clock.hpp>
#include <list>

namespace Szczur {
	class TimeEvents;
	
	class Time {
		friend class Game;
		friend class TimeEvents;
	
	public:
		static float time					();
		static float deltaTime				();
		static float realTime				();
		static float realDeltaTime			();
		static float fixedInterval			();
		
		static float speed					();
		static void  speed					(float speed);
		
		static void update					(void(*handler)());
		static void fixedUpdate				(void(*handler)());
		static void realFixedUpdate			(void(*handler)());
	
	private:
		Time() {} //Static class
		static void registerHandler			(TimeEvents* handler);
		static void unregisterHandler		(TimeEvents* handler);
	
		static float _time;
		static float _deltaTime;
		static float _realTime;
		static float _realDeltaTime;
		static float _fixedInterval;
		static float _speed;
		
		static sf::Clock timer;
		static float fixed;
		static float realFixed;
		static bool  isInitialize;
		
		static std::list<void(*)()>			updateHandlers;
		static std::list<void(*)()>			fixedUpdateHandlers;
		static std::list<void(*)()>			realFixedUpdateHandlers;
		static std::list<TimeEvents*>		handlers;
		
		
		static void init					();
		static void updateTimeSystem		();
	};
	
	class TimeEvents {
	public:
		TimeEvents() { Time::registerHandler(this); }
		
		virtual void update()				{};
		virtual void fixedUpdate()			{};
		virtual void realFixedUpdate()		{};
		
		virtual ~TimeEvents() { Time::unregisterHandler(this); }
	};
}
