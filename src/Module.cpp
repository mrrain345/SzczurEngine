#include <Szczur/Module.h>

namespace Szczur {
	std::list<Module*> Module::_modules;
	
	const char* Module::getName() {
		return _name;
	}
	
	uint32_t Module::getHash() {
		return _hash;
	}
	
	int Module::command(uint32_t sender, uint32_t command, void* data) { return MOD_BADCMD; }
	
	Module::~Module() {
		_modules.remove(this);
		delete[] _name;
	}
	
	int Module::send(uint32_t sender, uint32_t target, uint32_t command, void* data) {
		for (auto module: _modules) {
			if (target != module->getHash()) continue;
			return module->command(sender, command, data);
		}
		return MOD_NOTFOUND;
	}

	int Module::send(uint32_t target, uint32_t command, void* data) { 
		return send(_hash, target, command, data);
	}
}
