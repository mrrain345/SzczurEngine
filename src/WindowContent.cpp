#include <Szczur/Window.h>

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
	
	void WindowContent::Fill(Color color, unsigned char opacity) {
		sf::RectangleShape shape(Vector2(window->Width(), window->Height()));
		shape.setPosition(window->Position());
		
		float alpha = window->Opacity()/255.0f * opacity/255.0f;
		color.a = (unsigned char)(alpha * 255);
		shape.setFillColor(color);
		Game::Draw(shape);
	}
	
	void WindowContent::FillRect(Rect rect, Color color, unsigned char opacity) {
		float width = float(min(rect.width, window->Width() - rect.x));
		float height = float(min(rect.height, window->Height() - rect.y));
		
		sf::RectangleShape shape(Vector2(width, height));
		shape.setPosition(Vector2(rect.x + window->Position().x, rect.y + window->Position().y));
		
		float alpha = window->Opacity()/255.0f * opacity/255.0f;
		color.a = (unsigned char)(alpha * 255);
		shape.setFillColor(color);
		Game::Draw(shape);
	}
	
	void WindowContent::DrawText(Vector2 position, const char* str, unsigned int fontSize) {
		DrawText(position, std::string(str), Content::DefaultFont(), fontSize);
	}
	
	void WindowContent::DrawText(Vector2 position, const char* str, sf::Font& font, unsigned int fontSize) {
		DrawText(position, std::string(str), font, fontSize);
	}
	
	void WindowContent::DrawText(Vector2 position, sf::String str, unsigned int fontSize) {
		DrawText(position, str, Content::DefaultFont(), fontSize);
	}
	
	void WindowContent::DrawText(Vector2 position, sf::String str, sf::Font& font, unsigned int fontSize) {
		sf::Text text(str, font, fontSize);
		text.setPosition(position + window->Position());
		TEXT_SET_COLOR(text, textColor);
		Game::Draw(text);
	}
	
	float WindowContent::Animation(float begin, float end, std::function<float(float)> func, float state) {
		if (state < 0) state = 0;
		if (state > 1) state = 1;
		float dist = (end-begin) * func(state);
		return begin + dist;
	}
}
