#pragma once
#include <Szczur/System.h>
#include <Szczur/Window/WindowContent.h>

namespace Szczur {
	class Window {
	private:
		float inputDelay;
		unsigned char opacity;
		
	protected:
		Rect rect;
		WindowContent content;
		
		void SetActive();
	
	public:
		Window(unsigned char opacity = 255);
		Window(int width, int height, unsigned char opacity = 255);
		Window(int x, int y, int width, int height, unsigned char opacity = 255);
		Window(Rect rect, unsigned char opacity = 255);
		
		Vector2 Position();
		int Width();
		int Height();
		unsigned int Opacity();
		void Close();
		
		Vector2 GlobalToWindowCoords(Vector2 coords);
		Vector2 WindowToGlobalCoords(Vector2 coords);
		
		virtual void Refresh		() {}
		virtual void Update			() {}
		virtual void FixedUpdate	() {}
		virtual void RealFixedUpdate() {}
		virtual void OnClosed		() {}
		
		virtual void OnLostActive	() {}
		virtual void OnGainActive	() {}

		virtual void OnKeyPress		(Input::Key key) {}
		virtual void OnKeyRelease	(Input::Key key) {}
		virtual void OnKeyClick		(Input::Key key) {}

		virtual void OnMousePress	(Input::Button button) {}
		virtual void OnMouseRelease	(Input::Button button) {}
		virtual void OnMouseClick	(Input::Button button) {}
		virtual void OnMouseMove	(int x, int y) {}
		
		virtual ~Window() {};
	};
}
