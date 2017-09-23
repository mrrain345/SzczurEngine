#include "Menu/Menu.h"
#include "Inventory/Inventory.h"

namespace Szczur {
	void modulesInit() {
		new Module_Menu();
		new Module_Inventory();
	}
};
