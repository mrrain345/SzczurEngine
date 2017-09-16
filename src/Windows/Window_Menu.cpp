/*#include <Windows/Window_Menu.h>
#include <Windows/Window_Items.h>

namespace Szczur {
	Window_Menu::Window_Menu() {
		setActive();
		option = 0;
		options_count = 9;
		
		options[0] = sf::String(L"Przedmioty");
		options[1] = sf::String(L"Ekwipunek");
		options[2] = sf::String(L"Zadania");
		options[3] = sf::String(L"Bestiariusz");
		options[4] = sf::String(L"Mapa");
		options[5] = sf::String(L"Zapisz gre");
		options[6] = sf::String(L"Wczytaj gre");
		options[7] = sf::String(L"Ustawienia");
		options[8] = sf::String(L"Wyjdź");
	}
	
	void Window_Menu::refresh() {
		content.fill(Color::Black, 128);
		content.fillRect(Rect(32, 32, 320, Game::height() - 64), Color(32, 32, 32));
		
		content.fillRect(Rect(48, option * 32 + 48, 288, 32), Color::White);
		
		for (int i = 0; i < options_count; i++) {
			if (i == option) content.textColor = Color::Black;
			content.drawText(Vector2(48.0f, i * 32.0f + 48.0f), options[i], 24);
			if (i == option) content.textColor = Color::White;
		}
	}
	
	static Window* activeWindow = 0;
	static int activeOption = -1;
	
	void Window_Menu::onKeyPress(Input::Key key) {
		if (key == Input::KEY_ESCAPE) close();
		
		if (key == Input::KEY_UP) {
			option--;
			if (option < 0) option = options_count-1;
			Game::refresh();
		}
		
		if (key == Input::KEY_DOWN) {
			option++;
			if (option >= options_count) option = 0;
			Game::refresh();
		}

		if (key == Input::KEY_ENTER) {
			if (option == 0) { activeOption = option; activeWindow = new Window_Items(); }
			if (option == options_count - 1) Game::close();
		}
	}
	
	void Window_Menu::onMouseMove(int x, int y) {
		Rect rect = Rect(48, 48, 288, options_count * 32);
		if (!rect.contains(x, y)) return;
		
		if ((y - 48) / 32 == option) return;
		option = (y - 48) / 32;
		if (option < 0) option = 0;
		if (option > options_count - 1) option = options_count - 1;
		Game::refresh();
	}
	
	void Window_Menu::onMouseClick(Input::Button button) {
		if (button != Input::BTN_LEFT) return;
		
		int x = int(Input::mousePosition().x);
		int y = int(Input::mousePosition().y);
		
		Rect rect = Rect(48, 48, 288, options_count * 32);
		if (!rect.contains(x, y)) return;

		option = (y - 48) / 32;
		if (option < 0) option = 0;
		if (option > options_count - 1) option = options_count - 1;
		
		bool isCurrent = (activeOption == option);
		
		if (activeWindow != 0 || isCurrent) {
			activeWindow->close();
			activeWindow = 0;
			activeOption = -1;
			if (isCurrent) return;
		}
		
		onKeyPress(Input::KEY_ENTER);
	}
	
	void Window_Menu::onGainActive() {
		activeWindow = 0;
	}
}*/
