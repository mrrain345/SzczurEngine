#include <Szczur/System/Time.h>
#include <list>

namespace Szczur {
	float Time::time = 0;
	float Time::deltaTime = 0;
	float Time::realTime = 0;
	float Time::realDeltaTime = 0;
	float Time::fixedInterval = 0.2f;
	float Time::speed = 1;
	
	sf::Clock Time::timer;
	float Time::fixed = 0;
	float Time::realFixed = 0;
	bool  Time::isInitialize = false;
	
	std::list<std::function<void()>>	Time::update;
	std::list<std::function<void()>>	Time::fixedUpdate;
	std::list<std::function<void()>>	Time::realFixedUpdate;
	std::list<TimeEvents*>				Time::handlers;
	
	void Time::Init() {
		if (isInitialize) return;
		else isInitialize = true;
		timer.restart();
	}
	
	void Time::UpdateTimeSystem() {
		realDeltaTime = timer.getElapsedTime().asSeconds() - realTime;
		realTime += realDeltaTime;
		realFixed += realDeltaTime;
		
		deltaTime = realDeltaTime / speed;
		time += deltaTime;
		fixed += deltaTime;
		
		for (auto func: update) func();
		for (auto handler: handlers) handler->Update();
		
		if (realFixed >= fixedInterval) {
			realFixed -= fixedInterval;
			for (auto func: realFixedUpdate) func();
			for (auto handler: handlers) handler->RealFixedUpdate();
		}
		
		if (fixed >= fixedInterval) {
			fixed -= fixedInterval;
			for (auto func: fixedUpdate) func();
			for (auto handler: handlers) handler->FixedUpdate();
		}
	}
	
	float Time::GetTime()			{ return time; }
	float Time::DeltaTime()			{ return deltaTime; }
	float Time::RealTime()			{ return realTime; }
	float Time::RealDeltaTime()		{ return realDeltaTime; }
	float Time::GetFixedInterval()	{ return fixedInterval; }
	
	void Time::Update				(std::function<void()> handler)	{ update.push_back(handler); }
	void Time::FixedUpdate			(std::function<void()> handler)	{ fixedUpdate.push_back(handler); }
	void Time::RealFixedUpdate		(std::function<void()> handler)	{ realFixedUpdate.push_back(handler); }
	void Time::Register				(TimeEvents* handler)			{ handlers.push_back(handler); }
}
