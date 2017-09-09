#include <Windows/Window_Message.h>

namespace Szczur {
	Window_Message::Window_Message(CMD_Message* message) :Window(Game::Width()/2-300, Game::Height()-200, 600, 200) {
		this->message = message;
		time = 0;
		maxTime = message->time;
		letters = 0;
		SetActive();
	}
	
	void Window_Message::Refresh() {
		content.Fill(Color::Black, 192);
		content.DrawText(Vector2(32, 32), message->msg.substr(0, letters), 24);
	}
	
	void Window_Message::Update() {
		time += Time::DeltaTime();
		int letters = message->msg.length() * time / maxTime;
		if (letters > message->msg.length()) letters = message->msg.length();
		
		if (this->letters != letters) {
			this->letters = letters;
			Game::Refresh();
		}
	}
	
	void Window_Message::OnKeyPress(Input::Key key) {
		if (key == Input::KEY_Return || key == Input::KEY_Space) Close();
	}
	
	void Window_Message::OnClosed() {
		message->runState = 2;
	}
}
