#pragma once
#include <SFML/System/Clock.hpp>

#include <list>
#include <functional>

namespace Szczur {
	class TimeEvents;	
	
	class Time {
	private:
		Time() {} //Static class
		
		static float time;
		static float deltaTime;
		static float realTime;
		static float realDeltaTime;
		static float fixedInterval;
		
		static sf::Clock timer;
		static float fixed;
		static float realFixed;
		static bool  isInitialize;
		
		static std::list<std::function<void()>>	update;
		static std::list<std::function<void()>>	fixedUpdate;
		static std::list<std::function<void()>>	realFixedUpdate;
		static std::list<TimeEvents*>			handlers;
		
	public:
		static float speed;
		
		static void Init();
		static void UpdateTimeSystem();
		
		static float GetTime();
		static float DeltaTime();
		static float RealTime();
		static float RealDeltaTime();
		static float GetFixedInterval();
		
		static void Update			(std::function<void()> handler);
		static void FixedUpdate		(std::function<void()> handler);
		static void RealFixedUpdate	(std::function<void()> handler);
		static void Register		(TimeEvents* handler);
	};
	
	class TimeEvents {
	public:
		TimeEvents() { Time::Register(this); }
		
		virtual void Update() {};
		virtual void FixedUpdate() {};
		virtual void RealFixedUpdate() {};
	};
}
