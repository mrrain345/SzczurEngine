#include <Szczur/Types.h>
#include <Szczur/Window.h>
#include <SzczurEngine/WindowsManager.h>

namespace Szczur {
	Window::Window(unsigned char opacity) :content(this) {
		rect.x = 0;
		rect.y = 0;
		rect.width = Game::width();
		rect.height = Game::height();
		_opacity = opacity;
		WindowsManager::add(this);
	}
	
	Window::Window(int width, int height, unsigned char opacity) :content(this) {
		if (width > 0) {
			rect.x = (Game::width() - width)/2;
			rect.width = width;
		} else {
			rect.x = -width;
			rect.width = Game::width() + 2*width;
		}
		
		if (height > 0) {
			rect.y = (Game::height() - height)/2;
			rect.height = height;
		} else {
			rect.y = -height;
			rect.height = Game::height() + 2*height;
		}
		_opacity = opacity;
		WindowsManager::add(this);
	}
	
	Window::Window(int x, int y, int width, int height, unsigned char opacity) :content(this) {
		rect.x = x;
		rect.y = y;
		
		if(width > 0) rect.width = width;
		else rect.width = Game::width() - x + width;
		if(height > 0) rect.height = height;
		else rect.height = Game::height() - y + height;
		
		_opacity = opacity;
		WindowsManager::add(this);
	}
	
	Window::Window(Rect rect, unsigned char opacity) :content(this) {
		this->rect = rect;
		_opacity = opacity;
		WindowsManager::add(this);
	}
	
	Vector2 Window::position() { return Vector2(rect.x, rect.y); }
	
	int Window::width() { return rect.width; }
	int Window::height() { return rect.height; }
	unsigned char Window::opacity() { return _opacity; }
	
	Vector2 Window::globalToWindowCoords(Vector2 coords) { return coords - position(); }
	Vector2 Window::windowToGlobalCoords(Vector2 coords) { return coords + position(); }
	
	void Window::close() {
		WindowsManager::remove(this);
	};
	
	void Window::setActive() {
		WindowsManager::setActive(this);
	}
}
