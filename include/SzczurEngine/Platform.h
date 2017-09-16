#pragma once
#include <list>
#include <string>

namespace Szczur {
	std::list<std::string> listDirectory(const char* path);
	std::list<std::string> listModules();
	void* modopen(const char* name);
	void* dlopen(const char* name);
	void* dlsym(void* handle, const char* func);
	void dlclose(void* handle);
}
