#include <Windows/Window_Menu.h>
#include <Windows/Window_Items.h>

namespace Szczur {
	Window_Menu::Window_Menu() {
		SetActive();
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
	
	void Window_Menu::Refresh() {
		content.Fill(Color::Black, 128);
		content.FillRect(sf::IntRect(32, 32, 320, Game::Height() - 64), Color(32, 32, 32));
		
		content.FillRect(sf::IntRect(48, option * 32 + 48, 288, 32), Color::White);
		
		for (int i = 0; i < options_count; i++) {
			if (i == option) content.textColor = Color::Black;
			content.DrawText(Vector2(48.0f, i * 32.0f + 48.0f), options[i], 24);
			if (i == option) content.textColor = Color::White;
		}
	}
	
	static Window* activeWindow = 0;
	static int activeOption = -1;
	
	void Window_Menu::OnKeyPress(Input::Key key) {
		if (key == Input::KEY_Escape) Close();
		
		if (key == Input::KEY_Up) {
			option--;
			if (option < 0) option = options_count-1;
			Game::Refresh();
		}
		
		if (key == Input::KEY_Down) {
			option++;
			if (option >= options_count) option = 0;
			Game::Refresh();
		}

		if (key == Input::KEY_Return) {
			if (option == 0) { activeOption = option; activeWindow = new Window_Items(); }
			if (option == options_count - 1) Game::Close();
		}
	}
	
	void Window_Menu::OnMouseMove(int x, int y) {
		sf::IntRect rect = sf::IntRect(48, 48, 288, options_count * 32);
		if (!rect.contains(x, y)) return;
		
		if ((y - 48) / 32 == option) return;
		option = (y - 48) / 32;
		if (option < 0) option = 0;
		if (option > options_count - 1) option = options_count - 1;
		Game::Refresh();
	}
	
	void Window_Menu::OnMouseClick(Input::Button button) {
		if (button != Input::BUTTON_Left) return;
		
		int x = int(Input::GetMousePosition().x);
		int y = int(Input::GetMousePosition().y);
		
		sf::IntRect rect = sf::IntRect(48, 48, 288, options_count * 32);
		if (!rect.contains(x, y)) return;

		option = (y - 48) / 32;
		if (option < 0) option = 0;
		if (option > options_count - 1) option = options_count - 1;
		
		bool isCurrent = (activeOption == option);
		
		if (activeWindow != 0 || isCurrent) {
			activeWindow->Close();
			activeWindow = 0;
			activeOption = -1;
			if (isCurrent) return;
		}
		
		OnKeyPress(Input::KEY_Return);
	}
	
	void Window_Menu::OnGainActive() {
		activeWindow = 0;
	}
}
