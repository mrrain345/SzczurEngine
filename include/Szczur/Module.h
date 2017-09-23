#pragma once

#include <Szczur/Hash.h>
#include <cstring>
#include <stdint.h>
#include <list>

#define MOD_OK			( 0x00)

#define MOD_NOTFOUND	(-0x01)
#define MOD_BADCMD		(-0x02)
#define MOD_NOPERM		(-0x03)

namespace Szczur {
	class Module {
	public:
		template<size_t N>
		Module(const char (&name)[N]) {
			_name = new char[N];
			strcpy(_name, name);
			_hash = hash(name);
			_modules.push_back(this);
		}
		
		const char* getName();
		uint32_t getHash();
		
		virtual int command(uint32_t sender, uint32_t command, void* data);
		
		virtual ~Module();
		
		static int send(uint32_t sender, uint32_t target, uint32_t command, void* data);
		
		template<size_t N, size_t M, size_t O>
		static int send(const char (&sender)[N], const char (&target)[M], const char (&command)[O], void* data) {
			return send(hash(sender), hash(target), hash(command), data);
		}
	
	protected:
		int send(uint32_t target, uint32_t command, void* data);

		template<size_t N, size_t M>
		int send(const char (&target)[N], const char (&command)[M], void* data) { return send(hash(target), hash(command), data); }
	
	private:
		static std::list<Module*> _modules;
		
		uint32_t _hash;
		char* _name;
	
	};
}
