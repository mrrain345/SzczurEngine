#pragma once
#include <list>
#include <Window.h>
#include <Input.h>

namespace Szczur {
	class Window;
	
	class WindowsManager {
	private:
		WindowsManager() {} //Static class
		
		static std::list<Window*> actives;
		static std::list<Window*> windows;
		
		static void Update			();
		static void FixedUpdate		();
		static void RealFixedUpdate	();
		
		static void OnKeyPress		(Input::Key key);
		static void OnKeyRelease	(Input::Key key);
		static void OnKeyClick		(Input::Key key);
		static void OnMousePress	(Input::Button button);
		static void OnMouseRelease	(Input::Button button);
		static void OnMouseClick	(Input::Button button);
		static void OnMouseMove		(int x, int y);
		
		
		static float inputDelay;
		static bool isInitialize;
		
	public:
		static void Init();
		static int Count();
		
		static void Add(Window* window);
		static void Remove(Window* window);
		
		static void SetActive(Window* window);
		static Window* GetActive();
		static void Refresh();
	};
}
