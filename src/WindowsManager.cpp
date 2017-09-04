#include <WindowsManager.h>
#include <Time.h>
#include <Input.h>
#include <Game.h>

namespace Szczur {
	std::list<Window*> WindowsManager::actives;
	std::list<Window*> WindowsManager::windows;
	
	float WindowsManager::inputDelay = 0.2f;
	bool WindowsManager::isInitialize = false;
	
	void WindowsManager::Init() {
		if (isInitialize) return;
		else isInitialize = true;
		
		Time::Update			(Update);
		Time::FixedUpdate		(FixedUpdate);
		Time::RealFixedUpdate	(RealFixedUpdate);
		
		Input::KeyPress			(OnKeyPress);
		Input::KeyRelease		(OnKeyRelease);
		Input::KeyClick			(OnKeyClick);
		Input::MousePress		(OnMousePress);
		Input::MouseRelease		(OnMouseRelease);
		Input::MouseClick		(OnMouseClick);
		Input::MouseMove		(OnMouseMove);
	}
	
	int WindowsManager::Count() {
		return windows.size();
	}
	
	void WindowsManager::Add(Window* window) {
		windows.push_back(window);
		Game::Refresh();
	}
	
	void WindowsManager::Remove(Window* window) {
		window->OnClosed();
		bool active = GetActive() == window;
		actives.remove(window);
		windows.remove(window);
		delete window;
		inputDelay = 0.2f;
		if (active && GetActive()) GetActive()->OnGainActive();
		Game::Refresh();
	}
	
	void WindowsManager::SetActive(Window* window) {
		if (GetActive()) GetActive()->OnLostActive();
		inputDelay = 0.2f;
		actives.push_back(window);
		window->OnGainActive();
	}
	
	Window* WindowsManager::GetActive() {
		if (actives.size() == 0) return 0;
		return actives.back();
	}
	
	void WindowsManager::Refresh() {
		for (auto window: windows) window->Refresh();
	}
	
	void WindowsManager::Update() {
		if (inputDelay > 0) inputDelay -= Time::RealDeltaTime();
		if (inputDelay < 0) inputDelay = 0;
		if (inputDelay) return;
		for (auto window: windows) window->Update();
	}
	
	void WindowsManager::FixedUpdate	() { for (auto window: windows) window->FixedUpdate(); }
	void WindowsManager::RealFixedUpdate() { for (auto window: windows) window->RealFixedUpdate(); }
	
	void WindowsManager::OnKeyPress		(Input::Key key) { if (GetActive() && !inputDelay) GetActive()->OnKeyPress(key); }
	void WindowsManager::OnKeyRelease	(Input::Key key) { if (GetActive() && !inputDelay) GetActive()->OnKeyRelease(key); }
	void WindowsManager::OnKeyClick		(Input::Key key) { if (GetActive() && !inputDelay) GetActive()->OnKeyClick(key); }
	
	void WindowsManager::OnMousePress	(Input::Button button) { for (auto window: windows) window->OnMousePress(button); }
	void WindowsManager::OnMouseRelease	(Input::Button button) { for (auto window: windows) window->OnMouseRelease(button); }
	void WindowsManager::OnMouseClick	(Input::Button button) { for (auto window: windows) window->OnMouseClick(button); }
	void WindowsManager::OnMouseMove	(int x, int y) { for (auto window: windows) window->OnMouseMove(x - window->Position().x, y - window->Position().y); }
}
