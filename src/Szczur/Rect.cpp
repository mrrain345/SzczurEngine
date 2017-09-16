#include <Szczur/Rect.h>

namespace Szczur {
	Rect::Rect() {
		this->x = 0;
		this->y = 0;
		this->width = 0;
		this->height = 0;
	}
	
	Rect::Rect(int width, int height) {
		this->x = 0;
		this->y = 0;
		this->width = width;
		this->height = height;
	}
	
	Rect::Rect(int x, int y, int width, int height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
	
	Rect::Rect(Vector2 position, Vector2 size) {
		this->x = int(position.x);
		this->y = int(position.y);
		this->width = int(size.x);
		this->height = int(size.y);
	}
	
	Rect::Rect(sf::IntRect rect) {
		this->x = rect.left;
		this->y = rect.top;
		this->width = rect.width;
		this->height = rect.height;
	}
	
	void Rect::set(int x, int y, int width, int height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
	
	bool Rect::contains(int x, int y) {
		return (x >= this->x && y >= this->y && x <= this->x + this->width && y <= this->y + this->height);
	}
	
	bool Rect::contains(Vector2 point) {
		return (point.x >= x && point.y >= y && point.x <= x + width && point.y <= y + height);
	}
	
	bool Rect::contains(Rect rect) {
		return (rect.x >= x && rect.y >= y && rect.x + rect.width <= x + width && rect.y + rect.height <= y + height);
	}
	
	static int max(int a, int b) { return (a >= b) ? a : b; }
	static int min(int a, int b) { return (a <= b) ? a : b; }
	
	Rect Rect::commonPart(Rect rect1, Rect rect2) {
		int bx = max(rect1.x, rect2.x);
		int by = max(rect1.y, rect2.y);
		int ex = min(rect1.x + rect1.width, rect2.x + rect2.width);
		int ey = min(rect1.y + rect1.height, rect2.y + rect2.height);

		if (bx > ex || by > ey) return Rect();
		return Rect(bx, by, ex-bx, ey-by);
	}
	
	Rect::operator sf::IntRect() { return sf::IntRect(x, y, width, height); }
}
