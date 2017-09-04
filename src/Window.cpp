#include <Window.h>
#include <Game.h>

namespace Szczur {
	Window::Window(unsigned char opacity) :content(this) {
		rect.left = 0;
		rect.top = 0;
		rect.width = Game::Width();
		rect.height = Game::Height();
		this->opacity = opacity;
		WindowsManager::Add(this);
	}
	
	Window::Window(int width, int height, unsigned char opacity) :content(this) {
		if (width > 0) {
			rect.left = (Game::Width() - width)/2;
			rect.width = width;
		} else {
			rect.left = -width;
			rect.width = Game::Width() + 2*width;
		}
		
		if (height > 0) {
			rect.top = (Game::Height() - height)/2;
			rect.top = height;
		} else {
			rect.left = -height;
			rect.height = Game::Height() + 2*height;
		}
		this->opacity = opacity;
		WindowsManager::Add(this);
	}
	
	Window::Window(int x, int y, int width, int height, unsigned char opacity) :content(this) {
		rect.left = x;
		rect.top = y;
		
		if(width > 0) rect.width = width;
		else rect.width = Game::Width() - x + width;
		if(height > 0) rect.height = height;
		else rect.height = Game::Height() - y + height;
		
		this->opacity = opacity;
		WindowsManager::Add(this);
	}
	
	Window::Window(sf::IntRect rect, unsigned char opacity) :content(this) {
		this->rect = rect;
		this->opacity = opacity;
		WindowsManager::Add(this);
	}
	
	sf::Vector2f Window::Position() { return sf::Vector2f(rect.left, rect.top); }
	
	int Window::Width() { return rect.width; }
	int Window::Height() { return rect.height; }
	unsigned int Window::Opacity() { return opacity; }
	
	sf::Vector2f Window::GlobalToWindowCoords(sf::Vector2f coords) { return coords - Position(); }
	sf::Vector2f Window::WindowToGlobalCoords(sf::Vector2f coords) { return coords + Position(); }
	
	void Window::Close() {
		OnClosed();
		WindowsManager::Remove(this);
	};
	
	void Window::SetActive() {
		WindowsManager::SetActive(this);
	}
}
