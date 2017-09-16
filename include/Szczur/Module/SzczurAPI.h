#pragma once
#include <Szczur/Input.h>
#include <SFML/Graphics/Drawable.hpp>
#include <stdint.h>

namespace Szczur {
	class Window;
	
	struct SzczurAPI {
		uint32_t  hash_code;
		
		int		(*game_width)				();
		int		(*game_height)				();
		void	(*game_refresh)				();
		void	(*game_draw)				(const sf::Drawable& draw);
		void	(*game_close)				();

		bool	(*input_isKeyPressed)		(Input::Key key);
		bool	(*input_isKeyReleased)		(Input::Key key);
		bool	(*input_isMousePressed)		(Input::Button button);
		bool	(*input_isMouseReleased)	(Input::Button button);
		Vector2	(*input_mousePosition)	();

		void	(*input_keyPress)			(void(*handler)(Input::Key));
		void	(*input_keyRelease)			(void(*handler)(Input::Key));
		void	(*input_keyClick)			(void(*handler)(Input::Key));
		void	(*input_mousePress)			(void(*handler)(Input::Button));
		void	(*input_mouseRelease)		(void(*handler)(Input::Button));
		void	(*input_mouseClick)			(void(*handler)(Input::Button));
		void	(*input_mouseMove)			(void(*handler)(int, int));
		void	(*input_resize)				(void(*handler)(int, int));

		float	(*time_time)				();
		float	(*time_deltaTime)			();
		float	(*time_realTime)			();
		float	(*time_realDeltaTime)		();
		float	(*time_fixedInterval)		();

		void	(*time_speed_set)			(float speed);
		float	(*time_speed_get)			();

		void	(*time_update)				(void(*handler)());
		void	(*time_fixedUpdate)			(void(*handler)());
		void	(*time_realFixedUpdate)		(void(*handler)());

		void	(*windowsManager_add)		(Window* window);
		void	(*windowsManager_remove)	(Window* window);

		void	(*windowsManager_setActive)	(Window* window);
		Window*	(*windowsManager_getActive)	();
		
		int		(*module_send)				(uint32_t sender, uint32_t target, uint32_t command, void* data);
	};
}
