#include <Szczur/Window.h>
#include <SzczurEngine/Content.h>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#if SFML_VERSION_MINOR < 4
	#define TEXT_SET_COLOR(text, color) text.setColor(color)
#else
	#define TEXT_SET_COLOR(text, color) text.setFillColor(color)
#endif

namespace Szczur {
	static int min(int a, int b) { return (a <= b) ? a : b; }
	
	WindowContent::WindowContent(Window* window) {
		this->window = window;
		this->textColor = Color::White;
	}
	
	void WindowContent::fill(Color color, unsigned char opacity) {
		sf::RectangleShape shape(Vector2(window->width(), window->height()));
		shape.setPosition(window->position());
		
		float alpha = window->opacity()/255.0f * opacity/255.0f * color.a/255.0f;
		color.a = (unsigned char)(alpha * 255);
		shape.setFillColor(color);
		Game::draw(shape);
	}
	
	void WindowContent::fillRect(Rect rect, Color color, unsigned char opacity) {
		float width = float(min(rect.width, window->width() - rect.x));
		float height = float(min(rect.height, window->height() - rect.y));
		
		sf::RectangleShape shape(Vector2(width, height));
		shape.setPosition(Vector2(rect.x + window->position().x, rect.y + window->position().y));
		
		float alpha = window->opacity()/255.0f * opacity/255.0f * color.a/255.0f;
		color.a = (unsigned char)(alpha * 255);
		shape.setFillColor(color);
		Game::draw(shape);
	}
	
	void WindowContent::drawText(Vector2 position, const char* str, unsigned int fontSize) {
		drawText(position, str, Content::defaultFont(), fontSize);
	}
	
	void WindowContent::drawText(Vector2 position, const char* str, sf::Font& font, unsigned int fontSize) {
		sf::Text text(str, font, fontSize);
		text.setPosition(position + window->position());
		TEXT_SET_COLOR(text, textColor);
		Game::draw(text);
	}
	
	void WindowContent::drawText(Vector2 position, const wchar_t* str, unsigned int fontSize) {
		drawText(position, str, Content::defaultFont(), fontSize);
	}
	
	void WindowContent::drawText(Vector2 position, const wchar_t* str, sf::Font& font, unsigned int fontSize) {
		sf::Text text(str, font, fontSize);
		text.setPosition(position + window->position());
		TEXT_SET_COLOR(text, textColor);
		Game::draw(text);
	}
	
	float WindowContent::animation(float begin, float end, float(*func)(float), float state) {
		if (state < 0) state = 0;
		if (state > 1) state = 1;
		float dist = (end-begin) * func(state);
		return begin + dist;
	}
}
