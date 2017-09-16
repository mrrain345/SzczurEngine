#include <Szczur/Module.h>
#include <Szczur/Module/SzczurAPI.h>
#include <SzczurEngine/WindowsManager.h>
#include <iostream>

namespace Szczur {
	SzczurAPI* __szczur_api;
	uint32_t __szczur_hashCode;
	ModuleManifest* __szczur_manifest = NULL;	
	
	uint32_t module_getHash				()								{ return __szczur_hashCode; }

	int		Game::width					()								{ return __szczur_api->game_width				(); }
	int		Game::height				()								{ return __szczur_api->game_height				(); }
	void	Game::refresh				()								{		 __szczur_api->game_refresh				(); }
	void	Game::draw					(const sf::Drawable& draw)		{		 __szczur_api->game_draw				(draw); }
	void	Game::close					()								{		 __szczur_api->game_close				(); }

	bool	Input::isKeyPressed			(Input::Key key)				{ return __szczur_api->input_isKeyPressed		(key); }
	bool	Input::isKeyReleased		(Input::Key key)				{ return __szczur_api->input_isKeyReleased		(key); }
	bool	Input::isMousePressed		(Input::Button button)			{ return __szczur_api->input_isMousePressed		(button); }
	bool	Input::isMouseReleased		(Input::Button button)			{ return __szczur_api->input_isMouseReleased	(button); }
	Vector2	Input::mousePosition		()								{ return __szczur_api->input_mousePosition		(); }

	void	Input::keyPress				(void(*handler)(Input::Key))	{		 __szczur_api->input_keyPress			(handler); }
	void	Input::keyRelease			(void(*handler)(Input::Key))	{		 __szczur_api->input_keyRelease			(handler); }
	void	Input::keyClick				(void(*handler)(Input::Key))	{		 __szczur_api->input_keyClick			(handler); }
	void	Input::mousePress			(void(*handler)(Input::Button))	{		 __szczur_api->input_mousePress			(handler); }
	void	Input::mouseRelease			(void(*handler)(Input::Button))	{		 __szczur_api->input_mouseRelease		(handler); }
	void	Input::mouseClick			(void(*handler)(Input::Button))	{		 __szczur_api->input_mouseClick			(handler); }
	void	Input::mouseMove			(void(*handler)(int, int))		{		 __szczur_api->input_mouseMove			(handler); }
	void	Input::resize				(void(*handler)(int, int))		{		 __szczur_api->input_resize				(handler); }

	float	Time::time					()								{ return __szczur_api->time_time(); }
	float	Time::deltaTime				()								{ return __szczur_api->time_deltaTime			(); }
	float	Time::realTime				()								{ return __szczur_api->time_realTime			(); }
	float	Time::realDeltaTime			()								{ return __szczur_api->time_realDeltaTime		(); }
	float	Time::fixedInterval			()								{ return __szczur_api->time_fixedInterval		(); }

	void	Time::speed					(float speed)					{		 __szczur_api->time_speed_set			(speed); }
	float	Time::speed					()								{ return __szczur_api->time_speed_get			(); }

	void	Time::update				(void(*handler)())				{		 __szczur_api->time_update				(handler); }
	void	Time::fixedUpdate			(void(*handler)())				{		 __szczur_api->time_fixedUpdate			(handler); }
	void	Time::realFixedUpdate		(void(*handler)())				{		 __szczur_api->time_realFixedUpdate		(handler); }

	void	WindowsManager::add			(Window* window)				{		 __szczur_api->windowsManager_add		(window); }
	void	WindowsManager::remove		(Window* window)				{		 __szczur_api->windowsManager_remove	(window); }

	void	WindowsManager::setActive	(Window* window)				{		 __szczur_api->windowsManager_setActive	(window); }
	Window*	WindowsManager::getActive	()								{ return __szczur_api->windowsManager_getActive	(); }
}

void module_author		(const char* author)		{ Szczur::__szczur_manifest->author			= author; }
void module_description	(const char* description)	{ Szczur::__szczur_manifest->description	= description; }
void module_author		(std::string author)		{ Szczur::__szczur_manifest->author			= author; }
void module_description	(std::string description)	{ Szczur::__szczur_manifest->description	= description; }
void module_version		(float version)				{ Szczur::__szczur_manifest->version		= version; }

int module_send(uint32_t target, uint32_t command, void* data) {
	return Szczur::__szczur_api->module_send(Szczur::__szczur_hashCode, target, command, data);
}

extern "C" {
	void* _module_manifest() {
		if(Szczur::__szczur_manifest != NULL) return (void*)Szczur::__szczur_manifest;
		Szczur::__szczur_manifest = new Szczur::ModuleManifest;
		module_manifest();
		return (void*)Szczur::__szczur_manifest;
	}
	
	int _module_init(void* api, uint32_t hashCode) {
		Szczur::__szczur_api = (Szczur::SzczurAPI*) api;
		Szczur::__szczur_hashCode = hashCode;
		return module_init();
	}
	
	int _module_command(uint32_t sender, uint32_t command, void* data) {
		return module_command(sender, command, data);
	}
	
	void _module_close() {
		delete Szczur::__szczur_manifest;
		module_close();
	}
}
