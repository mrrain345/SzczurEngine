#include <WindowContent.h>
#include <Window.h>
#include <Game.h>
#include <iostream>

namespace Szczur {
	static int min(int a, int b) { if (a <= b) return a; return b; }
	
	WindowContent::WindowContent(Window* window) {
		this->window = window;
	}
	
	void WindowContent::Fill(sf::Color color, unsigned char opacity) {
		sf::RectangleShape shape(sf::Vector2f(window->Width(), window->Height()));
		shape.setPosition(window->Position());
		
		float alpha = window->Opacity()/255.0f * opacity/255.0f;
		color.a = (unsigned char)(alpha * 255);
		shape.setFillColor(color);
		Game::Draw(shape);
	}
	
	void WindowContent::FillRect(sf::IntRect rect, sf::Color color, unsigned char opacity) {
		int width = min(rect.width, window->Width() - rect.left);
		int height = min(rect.height, window->Height() - rect.top);
		
		sf::RectangleShape shape(sf::Vector2f(width, height));
		shape.setPosition(sf::Vector2f(rect.left + window->Position().x, rect.top + window->Position().y));
		
		float alpha = window->Opacity()/255.0f * opacity/255.0f;
		color.a = (unsigned char)(alpha * 255);
		shape.setFillColor(color);
		Game::Draw(shape);
	}
	
	void WindowContent::DrawText(sf::Vector2f position, const char* str, unsigned int fontSize) {
		sf::Text text(str, Game::defaultFont, fontSize);
		text.setPosition(position + window->Position());
		text.setColor(textColor);
		Game::Draw(text);
	}
	
	void WindowContent::DrawText(sf::Vector2f position, const char* str, sf::Font font, unsigned int fontSize) {
		sf::Text text(str, font, fontSize);
		text.setPosition(position + window->Position());
		text.setColor(textColor);
		Game::Draw(text);
	}
	
	void WindowContent::DrawText(sf::Vector2f position, sf::String str, unsigned int fontSize) {
		sf::Text text(str, Game::defaultFont, fontSize);
		text.setPosition(position + window->Position());
		text.setColor(textColor);
		Game::Draw(text);
	}
	
	void WindowContent::DrawText(sf::Vector2f position, sf::String str, sf::Font font, unsigned int fontSize) {
		sf::Text text(str, font, fontSize);
		text.setPosition(position + window->Position());
		text.setColor(textColor);
		Game::Draw(text);
	}
}
