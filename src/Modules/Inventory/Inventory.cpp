#include "Inventory.h"
#include "Window_Items.h"
#include <iostream>

struct CMD_OptionAdd {
	int position;
	const wchar_t* option;
	void(*callback)(size_t id);
};

static void menu_callback(size_t id) {
	std::cout << "Menu entry: " << id << std::endl;
	
	if (id == 0) new Window_Items();
}

Module_Inventory::Module_Inventory() :Module("inventory") {
	CMD_OptionAdd option0 {10, L"Przedmioty",	menu_callback};
	CMD_OptionAdd option1 {20, L"Zadania",		menu_callback};
	CMD_OptionAdd option2 {30, L"Bestiariusz",	menu_callback};
	CMD_OptionAdd option3 {40, L"Mapa",			menu_callback};
	CMD_OptionAdd option4 {50, L"Zapisz gre",	menu_callback};
	CMD_OptionAdd option5 {60, L"Wczytaj gre",	menu_callback};
	CMD_OptionAdd option6 {70, L"Ustawienia",	menu_callback};
	
	send("menu", "option-add", &option0);
	send("menu", "option-add", &option1);
	send("menu", "option-add", &option2);
	send("menu", "option-add", &option3);
	send("menu", "option-add", &option4);
	send("menu", "option-add", &option5);
	send("menu", "option-add", &option6);
}

int Module_Inventory::command(uint32_t sender, uint32_t command, void* data) {
	return MOD_BADCMD;
}
