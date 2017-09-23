#include "Window_Menu.h"
#include <Szczur/Types.h>

Window_Menu* window_menu = NULL;
std::list<MenuOption*> Window_Menu::options;

Window_Menu::Window_Menu() {
	setActive();
	option = 0;
}

static bool list_compare(const MenuOption* opt1, const MenuOption* opt2) {
	return (opt1->position < opt2->position);
}

int Window_Menu::addOption(MenuOption* option) {
	int id = 0;
	for (auto entry: options) if (entry->owner == option->owner) id++;
	
	option->id = id;
	options.push_back(option);
	options.sort(list_compare);
	
	return id;
}

void Window_Menu::refresh() {
	content.fill(Color::Black, 128);
	content.fillRect(Rect(32, 32, 320, Game::height() - 64), Color(32, 32, 32));
	
	content.fillRect(Rect(48, option * 32 + 48, 288, 32), Color::White);
	
	int i = 0;
	for (auto entry: options) {
		if (i == option) content.textColor = Color::Black;
		content.drawText(Vector2(48.0f, i * 32.0f + 48.0f), entry->option, 24);
		if (i == option) content.textColor = Color::White;
		i++;
	}
	
	if (i == option) content.textColor = Color::Black;
	content.drawText(Vector2(48.0f, i * 32.0f + 48.0f), L"Wyjście", 24);
	if (i == option) content.textColor = Color::White;
}

static Window* activeWindow = 0;
static int activeOption = -1;

void Window_Menu::onKeyPress(Input::Key key) {
	if (key == Input::KEY_ESCAPE) { window_menu = NULL; close(); }
	
	if (key == Input::KEY_UP) {
		option--;
		if (option < 0) option = options.size();
		Game::refresh();
	}
	
	if (key == Input::KEY_DOWN) {
		option++;
		if (option > options.size()) option = 0;
		Game::refresh();
	}

	if (key == Input::KEY_ENTER) {
		if (option == options.size()) {
			window_menu = NULL;
			close();
			Game::close();
		}
		
		int i = 0;
		for (auto entry: options) {
			if (i != option) { i++; continue; }
			entry->callback(entry->id);
			return;
		}
	}
}

void Window_Menu::onMouseMove(int x, int y) {
	Rect rect = Rect(48, 48, 288, (options.size()+1) * 32);
	if (!rect.contains(x, y)) return;
	
	if ((y - 48) / 32 == option) return;
	option = (y - 48) / 32;
	if (option < 0) option = 0;
	if (option > options.size()) option = options.size();
	Game::refresh();
}

void Window_Menu::onMouseClick(Input::Button button) {
	if (button != Input::BTN_LEFT) return;
	
	int x = int(Input::mousePosition().x);
	int y = int(Input::mousePosition().y);
	
	Rect rect = Rect(48, 48, 288, (options.size()+1) * 32);
	if (!rect.contains(x, y)) return;

	option = (y - 48) / 32;
	if (option < 0) option = 0;
	if (option > options.size()) option = options.size();
	
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
