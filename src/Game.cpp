#include <Szczur/System.h>
#include <Windows/Window_Title.h>

namespace Szczur {
	bool Game::refreshFlag;
	int Game::width;
	int Game::height;
	sf::RenderWindow Game::window;
	bool Game::isInitialize = false;
	
	sf::Font Game::defaultFont;

	void Game::Init(const char* title, int width, int height) {
		if (isInitialize) return;
		else isInitialize = true;
	
		Game::width = width;
		Game::height = height;
		refreshFlag = true;
		
		window.create(sf::VideoMode(width, height), title);
		
		Time::Init();
		Input::Init();
		WindowsManager::Init();
		
		defaultFont.loadFromFile("Fonts/OpenSans-Regular.ttf");
		
		new Window_Title;
		Loop();
	}

	void Game::Refresh() {
		refreshFlag = true;
	}
	
	void Game::Loop() {
		while (window.isOpen()) {
			Time::UpdateTimeSystem();
			
			sf::Event event;
			while (window.pollEvent(event)) {
				switch(event.type) {
					case sf::Event::Closed:					Close();						break;
					case sf::Event::KeyPressed:				Input::OnKeyPressed(event);		break;
					case sf::Event::KeyReleased:			Input::OnKeyReleased(event);	break;
					case sf::Event::MouseButtonPressed:		Input::OnMousePressed(event);	break;
					case sf::Event::MouseButtonReleased:	Input::OnMouseReleased(event);	break;
					case sf::Event::MouseMoved:				Input::OnMouseMoved(event);		break;
					case sf::Event::Resized:				Input::OnResized(event);		break;
				}
			}
			
			if(refreshFlag) {
				refreshFlag = false;
				window.clear();
				WindowsManager::Refresh();
				window.display();
			}
		}
	}

	void Game::Draw(const sf::Drawable& draw) {
		window.draw(draw);
	}

	void Game::Close() {
		window.close();
	}

	int Game::Width() {
		return width;
	}

	int Game::Height() {
		return height;
	}
}
