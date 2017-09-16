#define SZCZUR_CORE
#include <Szczur/Time.h>
#include <list>

namespace Szczur {
	float Time::_time			= 0;
	float Time::_deltaTime		= 0;
	float Time::_realTime		= 0;
	float Time::_realDeltaTime	= 0;
	float Time::_fixedInterval	= 0.2f;
	float Time::_speed			= 1;
	
	sf::Clock Time::timer;
	float Time::fixed			= 0;
	float Time::realFixed		= 0;
	bool  Time::isInitialize	= false;
	
	std::list<void(*)()>	Time::updateHandlers;
	std::list<void(*)()>	Time::fixedUpdateHandlers;
	std::list<void(*)()>	Time::realFixedUpdateHandlers;
	std::list<TimeEvents*>	Time::handlers;
	
	void Time::init() {
		if (isInitialize) return;
		else isInitialize = true;
		timer.restart();
	}
	
	void Time::updateTimeSystem() {
		_realDeltaTime = timer.getElapsedTime().asSeconds() - _realTime;
		_realTime += _realDeltaTime;
		realFixed += _realDeltaTime;
		
		_deltaTime = _realDeltaTime / _speed;
		_time += _deltaTime;
		fixed += _deltaTime;
		
		for (auto func: updateHandlers) func();
		for (auto handler: handlers) handler->update();
		
		if (realFixed >= _fixedInterval) {
			realFixed -= _fixedInterval;
			for (auto func: realFixedUpdateHandlers) func();
			for (auto handler: handlers) handler->realFixedUpdate();
		}
		
		if (fixed >= _fixedInterval) {
			fixed -= _fixedInterval;
			for (auto func: fixedUpdateHandlers) func();
			for (auto handler: handlers) handler->fixedUpdate();
		}
	}
	
	float Time::time			()	{ return _time; }
	float Time::deltaTime		()	{ return _deltaTime; }
	float Time::realTime		()	{ return _realTime; }
	float Time::realDeltaTime	()	{ return _realDeltaTime; }
	float Time::fixedInterval	()	{ return _fixedInterval; }
	
	float Time::speed			()	{ return _speed; }
	void  Time::speed(float speed)	{ _speed = speed; }
	
	void Time::update				(void(*handler)()) { updateHandlers.push_back(handler); }
	void Time::fixedUpdate			(void(*handler)()) { fixedUpdateHandlers.push_back(handler); }
	void Time::realFixedUpdate		(void(*handler)()) { realFixedUpdateHandlers.push_back(handler); }
	
	void Time::registerHandler		(TimeEvents* handler) { handlers.push_back(handler); }
	void Time::unregisterHandler	(TimeEvents* handler) { handlers.remove(handler); }
}

