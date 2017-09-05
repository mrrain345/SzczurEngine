#include <Szczur/System.h>

namespace Szczur {
	std::list<std::function<void(Input::Key)>>		Input::keyPress;
	std::list<std::function<void(Input::Key)>>		Input::keyRelease;
	std::list<std::function<void(Input::Key)>>		Input::keyClick;
	std::list<std::function<void(Input::Button)>>	Input::mousePress;
	std::list<std::function<void(Input::Button)>>	Input::mouseRelease;
	std::list<std::function<void(Input::Button)>>	Input::mouseClick;
	std::list<std::function<void(int, int)>>		Input::mouseMove;
	std::list<std::function<void(int, int)>>		Input::resize;
	std::list<InputEvents*>							Input::handlers;
	
	Input::Key Input::lastKey = KEY_Unknown;
	Input::Button Input::lastButton = BUTTON_Unknown;
	Vector2 Input::lastMousePos;
	
	void Input::Init() {}
	
	bool Input::IsKeyPressed	(Input::Key key)		{ return  sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key); }
	bool Input::IsKeyReleased	(Input::Key key)		{ return !sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key); }
	bool Input::IsMousePressed	(Input::Button button)	{ return  sf::Mouse::isButtonPressed((sf::Mouse::Button)button); }
	bool Input::IsMouseReleased	(Input::Button button)	{ return !sf::Mouse::isButtonPressed((sf::Mouse::Button)button); }
	
	Vector2 Input::GetMousePosition() {
		Vector2 pos = (Vector2)sf::Mouse::getPosition(Game::window);
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
		lastMousePos = Vector2(-1, -1);
	}
	
	void Input::OnMouseMoved(sf::Event event) {
		for (auto func: mouseMove) { Vector2 pos = GetMousePosition(); func(pos.x, pos.y); }
		for (auto handler: handlers) { Vector2 pos = GetMousePosition(); handler->OnMouseMove(pos.x, pos.y); }
	}
	
	void Input::OnResized(sf::Event event) {
		for (auto func: resize) func(event.size.width, event.size.height);
		for (auto handler: handlers) handler->OnResize(event.size.width, event.size.height);
		Game::Refresh();
	}
	
	void Input::KeyPress	(std::function<void(Input::Key)>	handler)	{ keyPress.push_back(handler); }
	void Input::KeyRelease	(std::function<void(Input::Key)>	handler)	{ keyRelease.push_back(handler); }
	void Input::KeyClick	(std::function<void(Input::Key)>	handler)	{ keyClick.push_back(handler); }
	void Input::MousePress	(std::function<void(Input::Button)>	handler)	{ mousePress.push_back(handler); }
	void Input::MouseRelease(std::function<void(Input::Button)>	handler)	{ mouseRelease.push_back(handler); }
	void Input::MouseClick	(std::function<void(Input::Button)>	handler)	{ mouseClick.push_back(handler); }
	void Input::MouseMove	(std::function<void(int, int)>		handler)	{ mouseMove.push_back(handler); }
	void Input::Resize		(std::function<void(int, int)>		handler)	{ resize.push_back(handler); }
	void Input::Register	(InputEvents* handler)							{ handlers.push_back(handler); }
}
