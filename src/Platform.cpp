#define SZCZUR_CORE
#include <SzczurEngine/Platform.h>

#ifdef __linux__
	#include <dirent.h>
	#include <dlfcn.h>

	namespace Szczur {
		std::list<std::string> listDirectory(const char* path) {
			struct dirent* file;
			DIR* dir;
	
			std::list<std::string> list;
	
			if (dir = opendir(path)) {
				while(file = readdir(dir)) {
					if (file->d_name[0] == '.') continue;
					list.push_back(std::string(file->d_name));
				};
				closedir(dir);
			}
			return list;
		}
	
		std::list<std::string> listModules() {
			std::list<std::string> modules = listDirectory("Modules");
			std::list<std::string> names;
			for (auto module: modules) {
				size_t len = module.size();
				if (len <= 3 || module.substr(len-3) != ".so") continue;
				names.push_back(module.substr(0, len-3));
			}
			return names;
		}
		
		void* modopen(const char* name) {
			return ::dlopen(("Modules/" + std::string(name) + ".so").c_str(), RTLD_LAZY);
		}
		
		void* dlopen(const char* name) {
			return ::dlopen((std::string(name) + ".so").c_str(), RTLD_LAZY);
		}
	
		void* dlsym(void* handle, const char* func) {
			return ::dlsym(handle, func);
		}
	
		void dlclose(void* handle) {
			::dlclose(handle);
		}
	}
#endif

#ifdef _WIN32
	#include <windows.h>
	
	namespace Szczur {
		std::list<std::string> listDirectory(const char* path) {
			WIN32_FIND_DATA data;
			HANDLE hFind = FindFirstFile(std::string(std::string(path) + "/*").c_str(), &data);
		
			std::list<std::string> list;

			if (hFind != INVALID_HANDLE_VALUE) {
				do {
					if (data.cFimeName[0] == '.') continue;
				    list.push_back(data.cFileName);
				} while (FindNextFile(hFind, &data));
				FindClose(hFind);
			}
			return list;
		}
	
		std::list<std::string> listModules() {
			std::list<std::string> modules = listDirectory("Modules");
			std::list<std::string> names;
			for (auto module: modules) {
				size_t len = module.size();
				if (len <= 4 || module.substr(len-4) != ".dll") continue;
				names.push_back(module.substr(0, len-4));
			}
			return names;
		}
		
		void* modopen(const char* name) {
			return LoadLibrary("Modules/" + (std::string(name) + ".dll").c_str());
		}
	
		void* dlopen(const char* name) {
			return LoadLibrary((std::string(name) + ".dll").c_str());
		}
	
		void* dlsym(void* handle, const char* func) {
			return GetProcAddress(handle, func);
		}
	
		void dlclose(void* handle) {
			FreeLibrary(handle);
		}
	}
#endif
