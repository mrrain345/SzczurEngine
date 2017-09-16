#include <Szczur/Module/SzczurAPI.h>
#include <Szczur/Module/ModuleManifest.h>
#include <Szczur/Hash.h>
#include <string>
#include <stdint.h>

#define MOD_OK			( 0x00)

#define MOD_NOTFOUND	(-0x01)
#define MOD_NOTLOADED	(-0x02)
#define MOD_INITFAULT	(-0x03)
#define MOD_DEPENDSLOOP	(-0x04)

#define MOD_NOTINIT		(-0x10)
#define MOD_REINIT		(-0x11)

#define MOD_BADCMD		(-0x20)
#define MOD_NOPERM		(-0x21)

namespace Szczur {
	extern ModuleManifest* __szczur_manifest;
}

int module_send(uint32_t target, uint32_t command, void* data);

template<size_t N, size_t M>
int module_send(const char (&target)[N], const char (&command)[M], void* data) { return module_send(hash(target), hash(command), data); }
	
uint32_t module_getHash();

void module_manifest();
int module_init();
int module_command(uint32_t sender, uint32_t command, void* data);
void module_close();

void module_author(const char* author);
void module_description(const char* description);
void module_author(std::string author);
void module_description(std::string description);
void module_version(float version);

template<size_t N>
void module_required(const char (&module)[N]) { Szczur::__szczur_manifest->required.push_back(hash(module)); }

template<size_t N>
void module_recommended(const char (&module)[N]) { Szczur::__szczur_manifest->recommended.push_back(hash(module)); }
