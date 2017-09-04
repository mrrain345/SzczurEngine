#pragma once
#include <SFML/System.hpp>
#include <list>

namespace Szczur {
	class TimeEvents {
	public:
		virtual void Update() {};
		virtual void FixedUpdate() {};
		virtual void RealFixedUpdate() {};
	};
	
	typedef void(*void_f)();
	
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
		static bool isInitialize;
		
		static std::list<void_f> update;
		static std::list<void_f> fixedUpdate;
		static std::list<void_f> realFixedUpdate;
		static std::list<TimeEvents*> handlers;
		
	public:
		static float speed;
		
		static void Init();
		static void UpdateTimeSystem();
		
		static float GetTime();
		static float DeltaTime();
		static float RealTime();
		static float RealDeltaTime();
		static float GetFixedInterval();
		
		static void Register(TimeEvents* handler);
		
		static void Update(void_f handler);
		static void FixedUpdate(void_f handler);
		static void RealFixedUpdate(void_f handler);
	};
}
