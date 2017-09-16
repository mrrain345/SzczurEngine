#pragma once
#include <Szczur/Window.h>
#include <Szczur/Input.h>

#include <list>

namespace Szczur {
	class Window;
	
	class WindowsManager {
	public:
		static void init();
		static int  count();
		
		static void add(Window* window);
		static void remove(Window* window);
		static void removeAll();
		
		static void setActive(Window* window);
		static Window* getActive();
		static void refresh();
	
	private:
		WindowsManager() {} //Static class
		
		static std::list<Window*> actives;
		static std::list<Window*> windows;
		
		static void update			();
		static void fixedUpdate		();
		static void realFixedUpdate	();
		
		static void onKeyPress		(Input::Key key);
		static void onKeyRelease	(Input::Key key);
		static void onKeyClick		(Input::Key key);
		static void onMousePress	(Input::Button button);
		static void onMouseRelease	(Input::Button button);
		static void onMouseClick	(Input::Button button);
		static void onMouseMove		(int x, int y);
		
		
		static float inputDelay;
		static bool  isInitialize;
	};
}
