#include <Windows/Window_Items.h>

namespace Szczur {
	Window_Items::Window_Items() :Window(384, 32, -32, -32) {
		SetActive();
		option = 0;
		options_count = 3;
		
		options[0] = sf::String(L"Item 1");
		options[1] = sf::String(L"Item 2");
		options[2] = sf::String(L"Item 3");
	}
	
	void Window_Items::Refresh() {
		content.FillRect(sf::IntRect(0, 0, rect.width, rect.height), Color(32, 32, 32));
		
		content.FillRect(sf::IntRect(16, option * 32 + 16, 288, 32), Color::White);
		
		for (int i = 0; i < options_count; i++) {
			if (i == option) content.textColor = Color::Black;
			content.DrawText(Vector2(16, i * 32 + 16), options[i], 24);
			if (i == option) content.textColor = Color::White;
		}
	}
	
	void Window_Items::OnKeyPress(Input::Key key) {
		if (key == Input::KEY_Escape) Close();
		if (key == Input::KEY_Up && option > 0) { option--; Game::Refresh(); }
		if (key == Input::KEY_Down && option < options_count-1) { option++; Game::Refresh(); }

		if (key == Input::KEY_Return) {
			
		}
	}
	
	void Window_Items::OnMouseMove(int x, int y) {
		sf::IntRect rect = sf::IntRect(16, 16, 288, options_count * 32);
		if (!rect.contains(x, y)) return;
		
		if ((y - 16) / 32 == option) return;
		option = (y - 16) / 32;
		if (option < 0) option = 0;
		if (option > options_count - 1) option = options_count - 1;
		Game::Refresh();
	}
}
