#define SZCZUR_CORE
#include <Szczur/Input.h>
#include <SzczurEngine/Game.h>

namespace Szczur {
	std::list<void(*)(Input::Key)>		Input::keyPressHandlers;
	std::list<void(*)(Input::Key)>		Input::keyReleaseHandlers;
	std::list<void(*)(Input::Key)>		Input::keyClickHandlers;
	std::list<void(*)(Input::Button)>	Input::mousePressHandlers;
	std::list<void(*)(Input::Button)>	Input::mouseReleaseHandlers;
	std::list<void(*)(Input::Button)>	Input::mouseClickHandlers;
	std::list<void(*)(int, int)>		Input::mouseMoveHandlers;
	std::list<void(*)(int, int)>		Input::resizeHandlers;
	std::list<InputEvents*>				Input::handlers;
	
	Input::Key Input::lastKey = KEY_UNKNOWN;
	Input::Button Input::lastButton = BTN_UNKNOWN;
	Vector2 Input::lastMousePos;
	
	void Input::init() {}
	
	bool Input::isKeyPressed	(Input::Key key)		{ return  sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key); }
	bool Input::isKeyReleased	(Input::Key key)		{ return !sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key); }
	bool Input::isMousePressed	(Input::Button button)	{ return  sf::Mouse::isButtonPressed((sf::Mouse::Button)button); }
	bool Input::isMouseReleased	(Input::Button button)	{ return !sf::Mouse::isButtonPressed((sf::Mouse::Button)button); }
	
	Vector2 Input::mousePosition() {
		Vector2 pos = (Vector2)sf::Mouse::getPosition(Game::window);
		pos.x *= (float)Game::width() / Game::window.getSize().x;
		pos.y *= (float)Game::height() / Game::window.getSize().y;
		return pos;
	}
	
	void Input::onKeyPressed(sf::Event event) {
		if (lastKey != (Key)event.key.code) {
			lastKey = (Key)event.key.code;
			for (auto func: keyPressHandlers) func((Key)event.key.code);
			for (auto handler: handlers) handler->onKeyPress((Key)event.key.code);
		}
	}
	
	void Input::onKeyReleased(sf::Event event) {
		for (auto func: keyReleaseHandlers) func((Key)event.key.code);
		for (auto handler: handlers) handler->onKeyRelease((Key)event.key.code);
		
		if (lastKey == (Key)event.key.code) {
			lastKey = KEY_UNKNOWN;
			for (auto func: keyClickHandlers) func((Key)event.key.code);
			for (auto handler: handlers) handler->onKeyClick((Key)event.key.code);
		}
	}
	
	void Input::onMousePressed(sf::Event event) {
		if (lastButton != (Button)event.mouseButton.button) {
			lastButton = (Button)event.mouseButton.button;
			lastMousePos = mousePosition();
			for (auto func: mousePressHandlers) func((Button)event.mouseButton.button);
			for (auto handler: handlers) handler->onMousePress((Button)event.mouseButton.button);
		}
	}
	
	void Input::onMouseReleased(sf::Event event) {
		for (auto func: mouseReleaseHandlers) func((Button)event.mouseButton.button);
		for (auto handler: handlers) handler->onMouseRelease((Button)event.mouseButton.button);
		
		if (lastButton == (Button)event.mouseButton.button && lastMousePos == mousePosition()) {
			for (auto func: mouseClickHandlers) func((Button)event.mouseButton.button);
			for (auto handler: handlers) handler->onMouseClick((Button)event.mouseButton.button);
		}
		
		lastButton = BTN_UNKNOWN;
		lastMousePos = Vector2(-1, -1);
	}
	
	void Input::onMouseMoved(sf::Event event) {
		for (auto func: mouseMoveHandlers) { Vector2 pos = mousePosition(); func(pos.x, pos.y); }
		for (auto handler: handlers) { Vector2 pos = mousePosition(); handler->onMouseMove(pos.x, pos.y); }
	}
	
	void Input::onResized(sf::Event event) {
		for (auto func: resizeHandlers) func(event.size.width, event.size.height);
		for (auto handler: handlers) handler->onResize(event.size.width, event.size.height);
		Game::refresh();
	}
	
	void Input::keyPress			(void(*handler)(Input::Key))	{ keyPressHandlers.push_back(handler); }
	void Input::keyRelease			(void(*handler)(Input::Key))	{ keyReleaseHandlers.push_back(handler); }
	void Input::keyClick			(void(*handler)(Input::Key))	{ keyClickHandlers.push_back(handler); }
	void Input::mousePress			(void(*handler)(Input::Button))	{ mousePressHandlers.push_back(handler); }
	void Input::mouseRelease		(void(*handler)(Input::Button))	{ mouseReleaseHandlers.push_back(handler); }
	void Input::mouseClick			(void(*handler)(Input::Button))	{ mouseClickHandlers.push_back(handler); }
	void Input::mouseMove			(void(*handler)(int, int))		{ mouseMoveHandlers.push_back(handler); }
	void Input::resize				(void(*handler)(int, int))		{ resizeHandlers.push_back(handler); }
	
	void Input::registerHandler		(InputEvents* handler)			{ handlers.push_back(handler); }
	void Input::unregisterHandler	(InputEvents* handler)			{ handlers.remove(handler); }
}
