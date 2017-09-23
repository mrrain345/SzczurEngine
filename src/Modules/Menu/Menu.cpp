#include "Menu.h"
#include "Window_Menu.h"
#include <cwchar>
#include <iostream>
#include <string>

struct CMD_OptionAdd {
	int position;
	const wchar_t* option;
	void(*callback)(size_t id);
};

int cmdWindowShow() {
	if (window_menu != NULL) return MOD_OK;
	window_menu = new Window_Menu;
	return MOD_OK;
}

int cmdWindowClose() {
	if (window_menu == NULL) return MOD_OK;
	window_menu->close();
	window_menu = NULL;
	return MOD_OK;
}

int cmdOptionAdd(uint32_t sender, CMD_OptionAdd* data) {
	MenuOption* option = new MenuOption();
	option->owner = sender;
	option->active = true;
	option->position = data->position;
	option->callback = data->callback;
	
	size_t len = wcslen(data->option)+1;
	option->option = new wchar_t[len];
	wcscpy(option->option, data->option);
	
	return Window_Menu::addOption(option);
}

int cmdOptionRemove		(uint32_t sender, size_t id) { return MOD_BADCMD; }
int cmdOptionActivate	(uint32_t sender, size_t id) { return MOD_BADCMD; }
int cmdOptionDeactivate	(uint32_t sender, size_t id) { return MOD_BADCMD; }

int Module_Menu::command(uint32_t sender, uint32_t command, void* data) {
	if (command == hash("window-show"))			return cmdWindowShow();
	if (command == hash("window-close"))		return cmdWindowClose();
	if (command == hash("option-add"))			return cmdOptionAdd(sender, (CMD_OptionAdd*)data);
	if (command == hash("option-remove"))		return cmdOptionRemove(sender, (size_t)data);
	if (command == hash("option-activate"))		return cmdOptionActivate(sender, (size_t)data);
	if (command == hash("option-deactivate"))	return cmdOptionDeactivate(sender, (size_t)data);
	
	return MOD_BADCMD;
}
