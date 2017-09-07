#include <Szczur/System.h>
#include <Szczur/Window.h>

namespace Szczur {
	Window::Window(unsigned char opacity) :content(this) {
		rect.x = 0;
		rect.y = 0;
		rect.width = Game::Width();
		rect.height = Game::Height();
		this->opacity = opacity;
		WindowsManager::Add(this);
	}
	
	Window::Window(int width, int height, unsigned char opacity) :content(this) {
		if (width > 0) {
			rect.x = (Game::Width() - width)/2;
			rect.width = width;
		} else {
			rect.x = -width;
			rect.width = Game::Width() + 2*width;
		}
		
		if (height > 0) {
			rect.y = (Game::Height() - height)/2;
			rect.height = height;
		} else {
			rect.y = -height;
			rect.height = Game::Height() + 2*height;
		}
		this->opacity = opacity;
		WindowsManager::Add(this);
	}
	
	Window::Window(int x, int y, int width, int height, unsigned char opacity) :content(this) {
		rect.x = x;
		rect.y = y;
		
		if(width > 0) rect.width = width;
		else rect.width = Game::Width() - x + width;
		if(height > 0) rect.height = height;
		else rect.height = Game::Height() - y + height;
		
		this->opacity = opacity;
		WindowsManager::Add(this);
	}
	
	Window::Window(Rect rect, unsigned char opacity) :content(this) {
		this->rect = rect;
		this->opacity = opacity;
		WindowsManager::Add(this);
	}
	
	Vector2 Window::Position() { return Vector2(rect.x, rect.y); }
	
	int Window::Width() { return rect.width; }
	int Window::Height() { return rect.height; }
	unsigned int Window::Opacity() { return opacity; }
	
	Vector2 Window::GlobalToWindowCoords(Vector2 coords) { return coords - Position(); }
	Vector2 Window::WindowToGlobalCoords(Vector2 coords) { return coords + Position(); }
	
	void Window::Close() {
		WindowsManager::Remove(this);
	};
	
	void Window::SetActive() {
		WindowsManager::SetActive(this);
	}
}
