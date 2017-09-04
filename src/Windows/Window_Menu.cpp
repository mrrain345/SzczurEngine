#include <Window_Menu.h>
#include <Game.h>
#include <Input.h>
#include <Window_Items.h>

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
		content.Fill(sf::Color::Black, 128);
		content.FillRect(sf::IntRect(32, 32, 320, Game::Height() - 64), sf::Color(32, 32, 32));
		
		content.FillRect(sf::IntRect(48, option * 32 + 48, 288, 32), sf::Color::White);
		
		for (int i = 0; i < options_count; i++) {
			if (i == option) content.textColor = sf::Color::Black;
			content.DrawText(sf::Vector2f(48, i * 32 + 48), options[i], 24);
			if (i == option) content.textColor = sf::Color::White;
		}
	}
	
	static Window* activeWindow = 0;
	
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
			if (option == 0) activeWindow = new Window_Items;
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
		
		int x = Input::GetMousePosition().x;
		int y = Input::GetMousePosition().y;
		
		sf::IntRect rect = sf::IntRect(48, 48, 288, options_count * 32);
		if (!rect.contains(x, y)) return;

		option = (y - 48) / 32;
		if (option < 0) option = 0;
		if (option > options_count - 1) option = options_count - 1;
		
		if (activeWindow != 0) {
			WindowsManager::Remove(activeWindow);
			activeWindow = 0;
		}
		
		OnKeyPress(Input::KEY_Return);
	}
	
	void Window_Menu::OnGainActive() {
		activeWindow = 0;
	}
}
