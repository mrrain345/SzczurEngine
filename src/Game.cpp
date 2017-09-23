#include <SzczurEngine/WindowsManager.h>
#include <SzczurEngine/Content.h>
#include <Szczur/Input.h>
#include <Szczur/Time.h>
#include <Windows/Window_Title.h>
#include <iostream>
#include <stdint.h>
#include <SFML/Graphics.hpp>


namespace Szczur {
	void modulesInit();
	
	bool Game::refreshFlag;
	int Game::_width;
	int Game::_height;
	sf::RenderWindow Game::window;
	bool Game::isInitialize = false;
	
	bool Game::switches[5000];
	
	void Game::init(const char* title, int width, int height) {
		if (isInitialize) return;
		else isInitialize = true;
	
		Game::_width = 1120;
		Game::_height = 640;
		refreshFlag = true;
		
		window.create(sf::VideoMode(width, height), title);
		for (int i = 0; i < 5000; i++) switches[i] = false;
		
		Time::init();
		Input::init();
		WindowsManager::init();
		
		Szczur::modulesInit();
		
		new Window_Title();
		
		loop();
	}
	
	void Game::refresh() {
		refreshFlag = true;
	}
	
#ifdef SZCZUR_EDITOR
	static void toolButton(float pos, int align = 0) {
		sf::RectangleShape button(Vector2(32, 32));
		button.setOrigin(16, 16);
		
		if(align == 0) button.setPosition(pos*48 + 24, 24);
		if(align == 1) button.setPosition(Game::window.getSize().x/2 + pos*48, 24);
		if(align == 2) button.setPosition(Game::window.getSize().x - pos*48 - 24, 24);
		
		button.setFillColor(Color(128));
		button.setOutlineColor(Color(64));
		button.setOutlineThickness(1);
		Game::draw(button);
	}
	
	void Game::drawToolbar() {
		Vector2 size = window.getSize();

		sf::View view(sf::FloatRect(0, 0, size.x, 49));
		view.setViewport(sf::FloatRect(0, 0, 1, 49/size.y));
		window.setView(view);
		
		sf::RectangleShape bground(Vector2(size.x, 48));
		bground.setPosition(0, 0);
		bground.setFillColor(Color(192));
		bground.setOutlineColor(Color(128));
		bground.setOutlineThickness(1);
		draw(bground);
		
		toolButton(0);
		toolButton(1);
		toolButton(2);
		
		toolButton(-1, 1);
		toolButton(0, 1);
		toolButton(1, 1);
		
		toolButton(0, 2);
		toolButton(1, 2);
		toolButton(2, 2);
	}
	
	void Game::drawInspector() {
		Vector2 size = window.getSize();

		sf::View view(sf::FloatRect(0, 0, 251, size.y));
		view.setViewport(sf::FloatRect(0, 49/size.y, 251/size.x, 1));
		window.setView(view);
		
		sf::RectangleShape bground(Vector2(250, size.y-49));
		bground.setPosition(0, 0);
		bground.setFillColor(Color(172));
		bground.setOutlineColor(Color(128));
		bground.setOutlineThickness(1);
		draw(bground);
	}
#endif
	
	void Game::drawGame() {
#ifdef SZCZUR_EDITOR
		Vector2 size = window.getSize();

		sf::View view(sf::FloatRect(0, 0, _width, _height));
		view.setViewport(sf::FloatRect(251/size.x, 49/size.y, _width/size.x, _height/size.y));
		window.setView(view);
#endif
		
		WindowsManager::refresh();
	}
	
	void Game::loop() {
		while (window.isOpen()) {
			Time::updateTimeSystem();
			
			sf::Event event;
			while (window.pollEvent(event)) {
				switch(event.type) {
					case sf::Event::Closed:					close();						break;
					case sf::Event::KeyPressed:				Input::onKeyPressed(event);		break;
					case sf::Event::KeyReleased:			Input::onKeyReleased(event);	break;
					case sf::Event::MouseButtonPressed:		Input::onMousePressed(event);	break;
					case sf::Event::MouseButtonReleased:	Input::onMouseReleased(event);	break;
					case sf::Event::MouseMoved:				Input::onMouseMoved(event);		break;
					case sf::Event::Resized:				Input::onResized(event);		break;
				}
			}
			
			if(refreshFlag) {
				refreshFlag = false;
				window.clear(Color(255));
#ifdef SZCZUR_EDITOR
				drawToolbar();
				drawInspector();
#endif
				drawGame();
				window.display();
			}
			
			//toolbar.clear();
			//toolbar.display();
		}
	}

	void Game::draw(const sf::Drawable& draw) {
		window.draw(draw);
	}

	void Game::close() {
		WindowsManager::removeAll();
		window.close();
		Content::close(&Content::defaultFont());
		Content::debugPrint();
		exit(0);
	}

	int Game::width() {
		return _width;
	}

	int Game::height() {
		return _height;
	}
}
