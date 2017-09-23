#include "Window_Items.h"

Window_Items::Window_Items() :Window(384, 32, -32, -32) {
	setActive();
	option = 0;
	
	options.push_back(L"Item 1");
	options.push_back(L"Item 2");
	options.push_back(L"Item 3");
}

void Window_Items::refresh() {
	content.fillRect(Rect(0, 0, rect.width, rect.height), Color(32, 32, 32));
	
	content.fillRect(Rect(16, option * 32 + 16, 288, 32), Color::White);
	
	int i = 0;
	for (auto item: options) {
		if (i == option) content.textColor = Color::Black;
		content.drawText(Vector2(16.0f, i * 32.0f + 16.0f), item, 24);
		if (i == option) content.textColor = Color::White;
		i++;
	}
}

void Window_Items::onKeyPress(Input::Key key) {
	if (key == Input::KEY_ESCAPE) close();
	if (key == Input::KEY_UP && option > 0) { option--; Game::refresh(); }
	if (key == Input::KEY_DOWN && option < options.size()-1) { option++; Game::refresh(); }

	if (key == Input::KEY_ENTER) {
		
	}
}

void Window_Items::onMouseMove(int x, int y) {
	Rect rect = Rect(16, 16, 288, options.size() * 32);
	if (!rect.contains(x, y)) return;
	
	if ((y - 16) / 32 == option) return;
	option = (y - 16) / 32;
	if (option < 0) option = 0;
	if (option > options.size() - 1) option = options.size() - 1;
	Game::refresh();
}
