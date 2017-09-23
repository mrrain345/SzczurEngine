#include <SzczurEngine/WindowsManager.h>
#include <Szczur/Types.h>

namespace Szczur {
	std::list<Window*> WindowsManager::actives;
	std::list<Window*> WindowsManager::windows;
	
	float WindowsManager::inputDelay = 0.2f;
	bool WindowsManager::isInitialize = false;
	
	void WindowsManager::init() {
		if (isInitialize) return;
		else isInitialize = true;
		
		Time::update			(update);
		Time::fixedUpdate		(fixedUpdate);
		Time::realFixedUpdate	(realFixedUpdate);
		
		Input::keyPress			(onKeyPress);
		Input::keyRelease		(onKeyRelease);
		Input::keyClick			(onKeyClick);
		Input::mousePress		(onMousePress);
		Input::mouseRelease		(onMouseRelease);
		Input::mouseClick		(onMouseClick);
		Input::mouseMove		(onMouseMove);
	}
	
	int WindowsManager::count() {
		return windows.size();
	}
	
	void WindowsManager::add(Window* window) {
		windows.push_back(window);
		Game::refresh();
	}
	
	void WindowsManager::remove(Window* window) {
		window->onClosed();
		bool active = (getActive() == window);
		actives.remove(window);
		windows.remove(window);
		delete window;
		inputDelay = 0.2f;
		if (active && getActive()) getActive()->onGainActive();
		Game::refresh();
	}
	
	void WindowsManager::removeAll() {
		for (int i = windows.size()-1; windows.size() != 0; i--) remove(windows.back());
	}
	
	void WindowsManager::setActive(Window* window) {
		if (getActive()) getActive()->onLostActive();
		inputDelay = 0.2f;
		actives.push_back(window);
		window->onGainActive();
	}
	
	Window* WindowsManager::getActive() {
		if (actives.size() == 0) return 0;
		return actives.back();
	}
	
	void WindowsManager::refresh() {
		for (auto window: windows) window->refresh();
	}
	
	void WindowsManager::update() {
		if (inputDelay > 0) inputDelay -= Time::realDeltaTime();
		if (inputDelay < 0) inputDelay = 0;
		if (inputDelay) return;
		for (auto window: windows) window->update();
	}
	
	void WindowsManager::fixedUpdate	() { for (auto window: windows) window->fixedUpdate(); }
	void WindowsManager::realFixedUpdate() { for (auto window: windows) window->realFixedUpdate(); }
	
	void WindowsManager::onKeyPress		(Input::Key key) { if (getActive() && !inputDelay) getActive()->onKeyPress(key); }
	void WindowsManager::onKeyRelease	(Input::Key key) { if (getActive() && !inputDelay) getActive()->onKeyRelease(key); }
	void WindowsManager::onKeyClick		(Input::Key key) { if (getActive() && !inputDelay) getActive()->onKeyClick(key); }
	
	void WindowsManager::onMousePress	(Input::Button button) { for (auto window: windows) window->onMousePress(button); }
	void WindowsManager::onMouseRelease	(Input::Button button) { for (auto window: windows) window->onMouseRelease(button); }
	void WindowsManager::onMouseClick	(Input::Button button) { for (auto window: windows) window->onMouseClick(button); }
	void WindowsManager::onMouseMove	(int x, int y) { for (auto window: windows) window->onMouseMove(x - window->position().x, y - window->position().y); }
}
