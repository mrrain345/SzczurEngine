#include <Windows/Window_Message.h>

namespace Szczur {
	Window_Message::Window_Message(CMD_Message* message) :Window(Game::width()/2-300, Game::height()-200, 600, 200) {
		this->message = message;
		time = 0;
		maxTime = message->time;
		letters = 0;
		setActive();
	}
	
	void Window_Message::refresh() {
		content.fill(Color::Black, 192);
		content.drawText(Vector2(32, 32), message->msg.substring(0, letters).toWideString().c_str(), 24);
	}
	
	void Window_Message::update() {
		time += Time::deltaTime();
		int size = message->msg.getSize();
		int letters = size * time / maxTime;
		if (letters > size) letters = size;
		
		if (this->letters != letters) {
			this->letters = letters;
			Game::refresh();
		}
	}
	
	void Window_Message::onKeyPress(Input::Key key) {
		if (key == Input::KEY_ENTER || key == Input::KEY_SPACE) close();
	}
	
	void Window_Message::onClosed() {
		message->runState = 2;
	}
}
