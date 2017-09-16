#pragma once
#include <Szczur/Input.h>
#include <Szczur/Time.h>
#include <Szczur/Types.h>
#include <Szczur/WindowContent.h>
#include <SzczurEngine/Game.h>

namespace Szczur {
	class Window {
	public:
		Window(unsigned char opacity = 255);
		Window(int width, int height, unsigned char opacity = 255);
		Window(int x, int y, int width, int height, unsigned char opacity = 255);
		Window(Rect rect, unsigned char opacity = 255);
		
		Vector2 position();
		int width();
		int height();
		unsigned char opacity();
		void close();
		
		Vector2 globalToWindowCoords(Vector2 coords);
		Vector2 windowToGlobalCoords(Vector2 coords);
		
		virtual void refresh		() {}
		virtual void update			() {}
		virtual void fixedUpdate	() {}
		virtual void realFixedUpdate() {}
		virtual void onClosed		() {}
		
		virtual void onLostActive	() {}
		virtual void onGainActive	() {}

		virtual void onKeyPress		(Input::Key key) {}
		virtual void onKeyRelease	(Input::Key key) {}
		virtual void onKeyClick		(Input::Key key) {}

		virtual void onMousePress	(Input::Button button) {}
		virtual void onMouseRelease	(Input::Button button) {}
		virtual void onMouseClick	(Input::Button button) {}
		virtual void onMouseMove	(int x, int y) {}
		
		virtual ~Window() {};
		
	protected:
		Rect rect;
		WindowContent content;
		
		void setActive();
		
	private:
		float inputDelay;
		unsigned char _opacity;
	};
}
