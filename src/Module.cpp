#include <SzczurEngine/Module.h>
#include <SzczurEngine/Platform.h>
#include <cstring>
#include <stdint.h>
#include <SzczurEngine/Game.h>

namespace Szczur {
	Module::Module(std::string name) {
		isInitialize = false;
		dependsTest = false;
		_name = name;
		
		size_t len = name.size() + 1;
		char* str = new char[len];
		
		memcpy(str, name.c_str(), len);
		_hash = ::hash(str, len);
		delete[] str;
		
		handle = modopen(name.c_str());
		
		_manifest	= (void*(*)())							dlsym(handle, "_module_manifest");
		_init		= (int	(*)(void*, uint32_t))			dlsym(handle, "_module_init");
		_close		= (void	(*)())							dlsym(handle, "_module_close");
		_command	= (int	(*)(uint32_t, uint32_t, void*))	dlsym(handle, "_module_command");
	}
	
	const char* Module::name() {
		return _name.c_str();
	}
	
	std::string Module::fullname() {
		ModuleManifest* man = manifest();
		std::string fullname = "'" + _name + "'" +
		((man->version != 0) ? " v" + std::to_string(man->version) : "") +
		((!man->author.empty()) ? " by <" + man->author + ">" : "");
		return fullname;
	}
	
	unsigned int Module::hash() {
		return _hash;
	}
	
	bool Module::initialized() {
		return isInitialize;
	}
	
	Module::~Module() {
		close();
		dlclose(handle);
	}
	
	ModuleManifest* Module::manifest() {
		return (ModuleManifest*) _manifest();
	}
	
	int Module::init(SzczurAPI* api) {
		if (isInitialize) return MOD_REINIT;
		isInitialize = true;
		return _init((void*)api, _hash);
	}
	
	void Module::close() {
		if (!isInitialize) return;
		_close();
	}
	
	int Module::send(uint32_t sender, uint32_t command, void* data) {
		if (!isInitialize) return MOD_NOTINIT;
		return _command(sender, command, data);
	}
	
	int Module::sendCommand(uint32_t target, uint32_t command, void* data) {
		return Game::moduleSend(::hash("system"), target, command, data);
	}
		
}
