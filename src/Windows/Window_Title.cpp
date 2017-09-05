#include <Window_Title.h>
#include <Window_Map.h>

namespace Szczur {
	Window_Title::Window_Title() {
		SetActive();
		
		option = 0;
		options_count = 4;
		
		options[0] = sf::String(L"Nowa Gra");
		options[1] = sf::String(L"Wczytaj Grę");
		options[2] = sf::String(L"Ustawienia");
		options[3] = sf::String(L"Wyjdź");
	}
	
	void Window_Title::Refresh() {
		int width = 280;
		int height = options_count * 32 + 32;
		int x = (Game::Width() - width) / 2;
		int y = Game::Height() - height - 64;
		
		content.Fill(Color(128, 128, 128));
		content.FillRect(sf::IntRect(x, y, width, height), Color(66, 66, 66));
		
		content.FillRect(sf::IntRect(x + 16,  y + 16 + option*32, width - 32, 32), Color::White);
		
		for (int i = 0; i < options_count; i++) {
			if (i == option) content.textColor = Color::Black;
			if (i == 1) content.textColor = Color(128, 128, 128);
			content.DrawText(Vector2(x + 16, y + 16 + i*32), options[i], 24);
			content.textColor = Color::White;
		}
	}
	
	void Window_Title::OnKeyPress(Input::Key key) {
		if (key == Input::KEY_Up && option > 0) {
			option--;
			if (option == 1) option--;
			Game::Refresh();
		}
		if (key == Input::KEY_Down && option < options_count-1) {
			option++;
			if (option == 1) option++;
			Game::Refresh();
		}
		
		if (key == Input::KEY_Return) {
			if (option == 0) {
				new Window_Map;
				Close();
			}
			if (option == options_count-1) Game::Close();
		}
	}
}
