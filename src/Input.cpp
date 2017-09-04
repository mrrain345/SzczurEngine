#include <Input.h>
#include <Game.h>
#include <iostream>

namespace Szczur {
	std::list<keyEvent_f>		Input::keyPress;
	std::list<keyEvent_f>		Input::keyRelease;
	std::list<keyEvent_f>		Input::keyClick;
	std::list<mouseEvent_f>		Input::mousePress;
	std::list<mouseEvent_f>		Input::mouseRelease;
	std::list<mouseEvent_f>		Input::mouseClick;
	std::list<mouseMoveEvent_f>	Input::mouseMove;
	std::list<resizeEvent_f>	Input::resize;
	std::list<InputEvents*>		Input::handlers;
	
	Input::Key Input::lastKey = KEY_Unknown;
	Input::Button Input::lastButton = BUTTON_Unknown;
	sf::Vector2f Input::lastMousePos;
	
	void Input::Init() {}
	
	bool Input::IsKeyPressed	(Input::Key key)		{ return  sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key); }
	bool Input::IsKeyReleased	(Input::Key key)		{ return !sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key); }
	bool Input::IsMousePressed	(Input::Button button)	{ return  sf::Mouse::isButtonPressed((sf::Mouse::Button)button); }
	bool Input::IsMouseReleased	(Input::Button button)	{ return !sf::Mouse::isButtonPressed((sf::Mouse::Button)button); }
	
	sf::Vector2f Input::GetMousePosition() {
		sf::Vector2f pos = (sf::Vector2f)sf::Mouse::getPosition(Game::window);
		pos.x *= (float)Game::Width() / Game::window.getSize().x;
		pos.y *= (float)Game::Height() / Game::window.getSize().y;
		return pos;
	}
	
	void Input::OnKeyPressed(sf::Event event) {
		if (lastKey != (Key)event.key.code) {
			lastKey = (Key)event.key.code;
			for (auto func: keyPress) func((Key)event.key.code);
			for (auto handler: handlers) handler->OnKeyPress((Key)event.key.code);
		}
	}
	
	void Input::OnKeyReleased(sf::Event event) {
		for (auto func: keyRelease) func((Key)event.key.code);
		for (auto handler: handlers) handler->OnKeyRelease((Key)event.key.code);
		
		if (lastKey == (Key)event.key.code) {
			lastKey = KEY_Unknown;
			for (auto func: keyClick) func((Key)event.key.code);
			for (auto handler: handlers) handler->OnKeyClick((Key)event.key.code);
		}
	}
	
	void Input::OnMousePressed(sf::Event event) {
		if (lastButton != (Button)event.mouseButton.button) {
			lastButton = (Button)event.mouseButton.button;
			lastMousePos = GetMousePosition();
			for (auto func: mousePress) func((Button)event.mouseButton.button);
			for (auto handler: handlers) handler->OnMousePress((Button)event.mouseButton.button);
		}
	}
	
	void Input::OnMouseReleased(sf::Event event) {
		for (auto func: mouseRelease) func((Button)event.mouseButton.button);
		for (auto handler: handlers) handler->OnMouseRelease((Button)event.mouseButton.button);
		
		if (lastButton == (Button)event.mouseButton.button && lastMousePos == GetMousePosition()) {
			for (auto func: mouseClick) func((Button)event.mouseButton.button);
			for (auto handler: handlers) handler->OnMouseClick((Button)event.mouseButton.button);
		}
		
		lastButton = BUTTON_Unknown;
		lastMousePos = sf::Vector2f(-1, -1);
	}
	
	void Input::OnMouseMoved(sf::Event event) {
		for (auto func: mouseMove) { sf::Vector2f pos = GetMousePosition(); func(pos.x, pos.y); }
		for (auto handler: handlers) { sf::Vector2f pos = GetMousePosition(); handler->OnMouseMove(pos.x, pos.y); }
	}
	
	void Input::OnResized(sf::Event event) {
		for (auto func: resize) func(event.size.width, event.size.height);
		for (auto handler: handlers) handler->OnResize(event.size.width, event.size.height);
		Game::Refresh();
	}
	
	void Input::KeyPress	(keyEvent_f handler)		{ keyPress.push_back(handler); }
	void Input::KeyRelease	(keyEvent_f handler)		{ keyRelease.push_back(handler); }
	void Input::KeyClick	(keyEvent_f handler)		{ keyClick.push_back(handler); }
	void Input::MousePress	(mouseEvent_f handler)		{ mousePress.push_back(handler); }
	void Input::MouseRelease(mouseEvent_f handler)		{ mouseRelease.push_back(handler); }
	void Input::MouseClick	(mouseEvent_f handler)		{ mouseClick.push_back(handler); }
	void Input::MouseMove	(mouseMoveEvent_f handler)	{ mouseMove.push_back(handler); }
	void Input::Resize		(resizeEvent_f handler)		{ resize.push_back(handler); }
	void Input::Register	(InputEvents* handler)		{ handlers.push_back(handler); }
}
