#pragma once
#include <Szczur/Module.h>

class Module_Inventory :public Szczur::Module {
public:
	Module_Inventory();
	int command(uint32_t sender, uint32_t command, void* data);
};
