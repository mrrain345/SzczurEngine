#pragma once
#include <list>
#include <string>

namespace Szczur {
	struct ModuleManifest {
		std::string author;
		std::string description;
		float version;
		std::list<unsigned int> required;
		std::list<unsigned int> recommended;
	};
}
