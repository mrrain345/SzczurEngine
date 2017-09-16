#define SZCZUR_CORE
#include <SzczurEngine/Platform.h>
#include <SzczurEngine/WindowsManager.h>
#include <SzczurEngine/Content.h>
#include <Szczur/Input.h>
#include <Szczur/Time.h>
#include <Windows/Window_Title.h>
#include <iostream>
#include <stdint.h>

//#define MODUL_DEBUG

namespace Szczur {
	bool Game::refreshFlag;
	int Game::_width;
	int Game::_height;
	sf::RenderWindow Game::window;
	bool Game::isInitialize = false;
	std::list<Module*> Game::modules;
	SzczurAPI* Game::moduleAPI;
	
	bool Game::switches[5000];

	void Game::init(const char* title, int width, int height) {
		if (isInitialize) return;
		else isInitialize = true;
	
		Game::_width = width;
		Game::_height = height;
		refreshFlag = true;
		
		window.create(sf::VideoMode(width, height), title);
		for (int i = 0; i < 5000; i++) switches[i] = false;
		
		Time::init();
		Input::init();
		WindowsManager::init();
		
		initAPI();
		modulesLoad();
		
		new Window_Title;
		loop();
	}
	
	void Game::initAPI() {
		moduleAPI = new SzczurAPI;
		
		moduleAPI->game_width					= Game::width;
		moduleAPI->game_height					= Game::height;
		moduleAPI->game_refresh					= Game::refresh;
		moduleAPI->game_draw					= Game::draw;
		moduleAPI->game_close					= Game::close;

		moduleAPI->input_isKeyPressed			= Input::isKeyPressed;
		moduleAPI->input_isKeyReleased			= Input::isKeyReleased;
		moduleAPI->input_isMousePressed			= Input::isMousePressed;
		moduleAPI->input_isMouseReleased		= Input::isMouseReleased;
		moduleAPI->input_mousePosition			= Input::mousePosition;

		moduleAPI->input_keyPress				= Input::keyPress;
		moduleAPI->input_keyRelease				= Input::keyRelease;
		moduleAPI->input_keyClick				= Input::keyClick;
		moduleAPI->input_mousePress				= Input::mousePress;
		moduleAPI->input_mouseRelease			= Input::mouseRelease;
		moduleAPI->input_mouseClick				= Input::mouseClick;
		moduleAPI->input_mouseMove				= Input::mouseMove;
		moduleAPI->input_resize					= Input::resize;

		moduleAPI->time_time					= Time::time;
		moduleAPI->time_deltaTime				= Time::deltaTime;
		moduleAPI->time_realTime				= Time::realTime;
		moduleAPI->time_realDeltaTime			= Time::realDeltaTime;
		moduleAPI->time_fixedInterval			= Time::fixedInterval;
		
		moduleAPI->time_speed_set				= Time::speed;
		moduleAPI->time_speed_get				= Time::speed;

		moduleAPI->time_update					= Time::update;
		moduleAPI->time_fixedUpdate				= Time::fixedUpdate;
		moduleAPI->time_realFixedUpdate			= Time::realFixedUpdate;

		moduleAPI->windowsManager_add			= WindowsManager::add;
		moduleAPI->windowsManager_remove		= WindowsManager::remove;

		moduleAPI->windowsManager_setActive		= WindowsManager::setActive;
		moduleAPI->windowsManager_getActive		= WindowsManager::getActive;

		moduleAPI->module_send					= Game::moduleSend;
	}
	
	int Game::moduleSend(uint32_t sender, uint32_t target, uint32_t command, void* data) {
		for (auto module: modules) {
			if (module->hash() == target) return module->send(sender, command, data);
		}
		return MOD_NOTFOUND;
	}
	
	void Game::modulesLoad() {
		std::list<std::string> moduleNames = listModules();
		for (auto moduleName: moduleNames) {
			#if MODULE_DEBUG
			std::cout << "Load module: '" << moduleName << "'";
			#endif
			Module* module = new Module(moduleName);
			#if MODULE_DEBUG
			std::cout << " (0x" << std::hex << module->hash() << ")" << std::endl;
			#endif
			modules.push_back(module);
		}
		
		for (auto module: modules) {
			if (moduleInit(module) < 0) {
				modules.remove(module);
				delete module;
			}
		}
	}
	
	int Game::moduleInit(Module* module) {
		if (module->initialized()) return MOD_OK;
		#if MODULE_DEBUG
		std::cout << std::endl << " *** Starting initialization of the module: " << module->fullname() << std::endl;
		#endif
		
		if (module->dependsTest) {
			std::cout << "ERROR: Dependencies loop in the module: '" << module->name() << "'" << std::endl;
			return MOD_DEPENDSLOOP;
		}
		
		ModuleManifest* manifest = module->manifest();
		
		if (manifest != NULL && manifest->required.size() > 0) {
			#if MODULE_DEBUG
			std::cout << "Solving required dependencies" << std::endl;
			#endif
			for (auto hash: manifest->required) {
				bool complete = false;
				for (auto required: modules) {
					if (hash != required->hash()) continue;
					if (required->initialized()) break;
					#if MODULE_DEBUG
					std::cout << "Starting initialization of required module: '" << required->name() << "'" << std::endl;
					#endif
					if (moduleInit(required) < 0) {
						std::cout << " ** ERROR: Module: '" << module->name() << "' wasn't loaded because of initialization fault of required module: '" << required->name() << "'" << std::endl;
						modules.remove(module);
						return MOD_INITFAULT;
					}
					#if MODULE_DEBUG
					std::cout << std::endl << " *** Initialization of required module '" << required->name() << "' complete. Back to the resolving dependencies of module: '" << module->name() << "'" << std::endl;
					#endif
					complete = true;
				}
				if (complete) continue;
				std::cout << " ** ERROR: Module: '" << module->name() << "' didn't load because of didn't find required module (0x" << std::hex << hash << ")" << std::endl;
				modules.remove(module);
				return MOD_INITFAULT;
			}
		}
		
		if (manifest != NULL && manifest->recommended.size() > 0) {
			#if MODULE_DEBUG
			std::cout << "Solving recommended dependencies" << std::endl;
			#endif
			for (auto hash: manifest->recommended) {
				for (auto recommended: modules) {
					if (hash != recommended->hash()) continue;
					if (recommended->initialized()) break;
					if (moduleInit(recommended) < 0) {
						#if MODULE_DEBUG
						std::cout << " * Recommended module: '" << recommended->name() << "' by module: '" << module->name() << "' wasn't loaded" << std::endl;
						#endif
					}
					break;
				}
				#if MODULE_DEBUG
				std::cout << " * Recommended module (0x" << std::hex << hash << ") by module: '" << module->name() << "' wasn't found" << std::endl;
				#endif
			}
		}
		
		#if MODULE_DEBUG
		std::cout << " * Initialization of the module: '" << module->name() << "'" << std::endl;
		#endif
		int ret = module->init(moduleAPI);
		if (ret < 0) {
			std::cout << " *** ERROR[" << ret << "]: Error during initialization of the module: '" << module->name() << "'" << std::endl;
			return MOD_INITFAULT;
		}
		return MOD_OK;
	}
	
	void Game::modulesClose() {
		for (auto module: modules) delete module;
		modules.clear();
		delete moduleAPI;
	}
	
	void Game::refresh() {
		refreshFlag = true;
	}
	
	void Game::loop() {
		while (window.isOpen()) {
			Time::updateTimeSystem();
			
			sf::Event event;
			while (window.pollEvent(event)) {
				switch(event.type) {
					case sf::Event::Closed:					close();						break;
					case sf::Event::KeyPressed:				Input::onKeyPressed(event);		break;
					case sf::Event::KeyReleased:			Input::onKeyReleased(event);	break;
					case sf::Event::MouseButtonPressed:		Input::onMousePressed(event);	break;
					case sf::Event::MouseButtonReleased:	Input::onMouseReleased(event);	break;
					case sf::Event::MouseMoved:				Input::onMouseMoved(event);		break;
					case sf::Event::Resized:				Input::onResized(event);		break;
				}
			}
			
			if(refreshFlag) {
				refreshFlag = false;
				window.clear();
				WindowsManager::refresh();
				window.display();
			}
		}
	}

	void Game::draw(const sf::Drawable& draw) {
		window.draw(draw);
	}

	void Game::close() {
		modulesClose();
		WindowsManager::removeAll();
		window.close();
		Content::close(&Content::defaultFont());
		Content::debugPrint();
		exit(0);
	}

	int Game::width() {
		return _width;
	}

	int Game::height() {
		return _height;
	}
}
