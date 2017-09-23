#pragma once
#include <Szczur/Module.h>

class Module_Menu :public Szczur::Module {
public:
	Module_Menu() :Module("menu") {}
	
	int command(uint32_t sender, uint32_t command, void* data);
};
