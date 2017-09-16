#include <Szczur/Module.h>
#include <iostream>
#include <stdint.h>

void menu_callback(size_t id) {
	std::cout << "Menu entry: " << id << std::endl;
}

void module_manifest() {
	module_author("MrRaiN");
	module_description("Inventory option in game menu");
	module_version(0.001);
	module_required("menu");
}

struct MenuOption {
	int index;
	const wchar_t* option;
	void(*callback)(size_t id);
};

int module_init() {
	
	MenuOption option0 {10, L"Przedmioty", menu_callback};
	MenuOption option1 {20, L"Zadania", menu_callback};
	MenuOption option2 {30, L"Bestiariusz", menu_callback};
	MenuOption option3 {40, L"Mapa", menu_callback};
	MenuOption option4 {50, L"Zapisz gre", menu_callback};
	MenuOption option5 {60, L"Wczytaj gre", menu_callback};
	MenuOption option6 {70, L"Ustawienia", menu_callback};
	
	module_send("menu", "option-add", &option0);
	module_send("menu", "option-add", &option1);
	module_send("menu", "option-add", &option2);
	module_send("menu", "option-add", &option3);
	module_send("menu", "option-add", &option4);
	module_send("menu", "option-add", &option5);
	module_send("menu", "option-add", &option6);
	
	return MOD_OK;
}

int module_command(unsigned int sender, unsigned int command, void* data) {
	return MOD_BADCMD;
}

void module_close() {}
