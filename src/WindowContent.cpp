#include <Szczur/Window.h>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace Szczur {
	static int min(int a, int b) { return (a <= b) ? a : b; }
	
	WindowContent::WindowContent(Window* window) {
		this->window = window;
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
		int width = min(rect.width, window->Width() - rect.x);
		int height = min(rect.height, window->Height() - rect.y);
		
		sf::RectangleShape shape(Vector2(width, height));
		shape.setPosition(Vector2(rect.x + window->Position().x, rect.y + window->Position().y));
		
		float alpha = window->Opacity()/255.0f * opacity/255.0f;
		color.a = (unsigned char)(alpha * 255);
		shape.setFillColor(color);
		Game::Draw(shape);
	}
	
	void WindowContent::DrawText(Vector2 position, const char* str, unsigned int fontSize) {
		sf::Text text(str, Game::defaultFont, fontSize);
		text.setPosition(position + window->Position());
		text.setColor(textColor);
		Game::Draw(text);
	}
	
	void WindowContent::DrawText(Vector2 position, const char* str, sf::Font font, unsigned int fontSize) {
		sf::Text text(str, font, fontSize);
		text.setPosition(position + window->Position());
		text.setColor(textColor);
		Game::Draw(text);
	}
	
	void WindowContent::DrawText(Vector2 position, sf::String str, unsigned int fontSize) {
		sf::Text text(str, Game::defaultFont, fontSize);
		text.setPosition(position + window->Position());
		text.setColor(textColor);
		Game::Draw(text);
	}
	
	void WindowContent::DrawText(Vector2 position, sf::String str, sf::Font font, unsigned int fontSize) {
		sf::Text text(str, font, fontSize);
		text.setPosition(position + window->Position());
		text.setColor(textColor);
		Game::Draw(text);
	}
}
