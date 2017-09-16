#pragma once
#include <string>
#include <Szczur/Hash.h>
#include <Szczur/Module/ModuleManifest.h>
#include <stdint.h>
#include <list>

#define MOD_OK			( 0x00)

#define MOD_NOTFOUND	(-0x01)
#define MOD_NOTLOADED	(-0x02)
#define MOD_INITFAULT	(-0x03)
#define MOD_DEPENDSLOOP	(-0x04)

#define MOD_NOTINIT		(-0x10)
#define MOD_REINIT		(-0x11)

#define MOD_BADCMD		(-0x20)

namespace Szczur {
	class SzczurAPI;
	
	class Module {
		friend class Game;
	
	public:
		Module(std::string name);
		
		const char* name();
		std::string fullname();
		unsigned int hash();
		bool initialized();
		
		template<size_t N, size_t M>
		inline int send(const char (&sender)[N], const char (&command)[M], void* data) { return send(::hash(sender), ::hash(command), data); }
		int send(uint32_t sender, uint32_t command, void* data);
		
		~Module();
		
		template<size_t N, size_t M>
		static inline int sendCommand(const char (&target)[N], const char (&command)[M], void* data) { return sendCommand(::hash(target), ::hash(command), data); }
		static int sendCommand(uint32_t target, uint32_t command, void* data);
		
	private:
		static std::list<Module*> modules;
		
		void* handle;
		std::string _name;
		unsigned int _hash;
		bool isInitialize;
		bool dependsTest;
		
		void*(*_manifest)();
		int(*_init)(void* api, uint32_t hashCode);
		void(*_close)();
		int(*_command)(uint32_t sender, uint32_t command, void* data);
		
		ModuleManifest* manifest();
		int init(SzczurAPI* api);
		void close();
	};
}
