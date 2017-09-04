#pragma once
#include <SFML/Graphics.hpp>
#include <WindowsManager.h>
#include <WindowContent.h>
#include <Input.h>

namespace Szczur {
	class Window {
	private:
		float inputDelay;
		unsigned char opacity;
		
	protected:
		sf::IntRect rect;
		WindowContent content;
		
		void SetActive();
	
	public:
		Window(unsigned char opacity = 255);
		Window(int width, int height, unsigned char opacity = 255);
		Window(int x, int y, int width, int height, unsigned char opacity = 255);
		Window(sf::IntRect rect, unsigned char opacity = 255);
		
		sf::Vector2f Position();
		int Width();
		int Height();
		unsigned int Opacity();
		void Close();
		
		sf::Vector2f GlobalToWindowCoords(sf::Vector2f coords);
		sf::Vector2f WindowToGlobalCoords(sf::Vector2f coords);
		
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
	};
}
