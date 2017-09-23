#pragma once
#include <Szczur/Vector2.h>
#include <list>
#include <SFML/Window.hpp>

namespace Szczur {
	class InputEvents;
	class Input {
		friend class Game;
		friend class InputEvents;
	
	public:
		enum Key {
			KEY_UNKNOWN = -1, ///< Unhandled key
			KEY_A = 0,        ///< The A key
			KEY_B,            ///< The B key
			KEY_C,            ///< The C key
			KEY_D,            ///< The D key
			KEY_E,            ///< The E key
			KEY_F,            ///< The F key
			KEY_G,            ///< The G key
			KEY_H,            ///< The H key
			KEY_I,            ///< The I key
			KEY_J,            ///< The J key
			KEY_K,            ///< The K key
			KEY_L,            ///< The L key
			KEY_M,            ///< The M key
			KEY_N,            ///< The N key
			KEY_O,            ///< The O key
			KEY_P,            ///< The P key
			KEY_Q,            ///< The Q key
			KEY_R,            ///< The R key
			KEY_S,            ///< The S key
			KEY_T,            ///< The T key
			KEY_U,            ///< The U key
			KEY_V,            ///< The V key
			KEY_W,            ///< The W key
			KEY_X,            ///< The X key
			KEY_Y,            ///< The Y key
			KEY_Z,            ///< The Z key
			KEY_0,            ///< The 0 key
			KEY_1,            ///< The 1 key
			KEY_2,            ///< The 2 key
			KEY_3,            ///< The 3 key
			KEY_4,            ///< The 4 key
			KEY_5,            ///< The 5 key
			KEY_6,            ///< The 6 key
			KEY_7,            ///< The 7 key
			KEY_8,            ///< The 8 key
			KEY_9,            ///< The 9 key
			KEY_ESCAPE,       ///< The Escape key
			KEY_CONTROL,      ///< The left Control key
			KEY_SHIFT,        ///< The left Shift key
			KEY_ALT,          ///< The left Alt key
			KEY_SUPER,        ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
			KEY_RCONTROL,     ///< The right Control key
			KEY_RSHIFT,       ///< The right Shift key
			KEY_RALT,         ///< The right Alt key
			KEY_RSUPER,       ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
			KEY_MENU,         ///< The Menu key
			KEY_LBRACKET,     ///< The [ key
			KEY_RBRACKET,     ///< The ] key
			KEY_SEMICOLON,    ///< The ; key
			KEY_COMMA,        ///< The , key
			KEY_PERIOD,       ///< The . key
			KEY_QUOTE,        ///< The ' key
			KEY_SLASH,        ///< The / key
			KEY_BACKSLASH,    ///< The \ key
			KEY_TILDE,        ///< The ~ key
			KEY_EQUAL,        ///< The = key
			KEY_DASH,         ///< The - key
			KEY_SPACE,        ///< The Space key
			KEY_ENTER,        ///< The Enter key
			KEY_BACKSPACE,    ///< The Backspace key
			KEY_TAB,          ///< The Tabulation key
			KEY_PAGEUP,       ///< The Page up key
			KEY_PAGEDOWN,     ///< The Page down key
			KEY_END,          ///< The End key
			KEY_HOME,         ///< The Home key
			KEY_INSERT,       ///< The Insert key
			KEY_DELETE,       ///< The Delete key
			KEY_ADD,          ///< The + key
			KEY_SUBTRACT,     ///< The - key
			KEY_MULTIPLY,     ///< The * key
			KEY_DIVIDE,       ///< The / key
			KEY_LEFT,         ///< Left arrow
			KEY_RIGHT,        ///< Right arrow
			KEY_UP,           ///< Up arrow
			KEY_DOWN,         ///< Down arrow
			KEY_NUM0,         ///< The numpad 0 key
			KEY_NUM1,         ///< The numpad 1 key
			KEY_NUM2,         ///< The numpad 2 key
			KEY_NUM3,         ///< The numpad 3 key
			KEY_NUM4,         ///< The numpad 4 key
			KEY_NUM5,         ///< The numpad 5 key
			KEY_NUM6,         ///< The numpad 6 key
			KEY_NUM7,         ///< The numpad 7 key
			KEY_NUM8,         ///< The numpad 8 key
			KEY_NUM9,         ///< The numpad 9 key
			KEY_F1,           ///< The F1 key
			KEY_F2,           ///< The F2 key
			KEY_F3,           ///< The F3 key
			KEY_F4,           ///< The F4 key
			KEY_F5,           ///< The F5 key
			KEY_F6,           ///< The F6 key
			KEY_F7,           ///< The F7 key
			KEY_F8,           ///< The F8 key
			KEY_F9,           ///< The F9 key
			KEY_F10,          ///< The F10 key
			KEY_F11,          ///< The F11 key
			KEY_F12,          ///< The F12 key
			KEY_F13,          ///< The F13 key
			KEY_F14,          ///< The F14 key
			KEY_F15,          ///< The F15 key
			KEY_PAUSE,        ///< The Pause key

			KEYCOUNT          ///< Keep last -- the total number of keyboard keys
		};
		
		enum Button {
			BTN_UNKNOWN = -1, ///< Unhandled button
			BTN_LEFT = 0,     ///< The left mouse button
			BTN_RIGHT,        ///< The right mouse button
			BTN_MIDDLE,       ///< The middle (wheel) mouse button
			BTN_XBUTTON1,     ///< The first extra mouse button
			BTN_XBUTTON2,     ///< The second extra mouse button

			BUTTONCOUNT       ///< Keep last -- the total number of mouse buttons
		};
		
		enum Wheel {
			WHEEL_UNKNOWN = -1,  ///< Unhandled wheel
			WHEEL_VERTICAL = 0,  ///< The vertical mouse wheel
			WHEEL_HORIZONTAL     ///< The horizontal mouse wheel
		};
	
	public:
		static bool isKeyPressed		(Key key);
		static bool isKeyReleased		(Key key);
		static bool isMousePressed		(Button button);
		static bool isMouseReleased		(Button button);
		
		static Vector2 mousePosition	();
		
		static void keyPress			(void(*handler)(Key));
		static void keyRelease			(void(*handler)(Key));
		static void keyClick			(void(*handler)(Key));
		static void mousePress			(void(*handler)(Button));
		static void mouseRelease		(void(*handler)(Button));
		static void mouseClick			(void(*handler)(Button));
		static void mouseMove			(void(*handler)(int, int));
		static void resize				(void(*handler)(int, int));
	
	private:
		Input() {} //Static class
		
		static void registerHandler		(InputEvents* handler);
		static void unregisterHandler	(InputEvents* handler);
		
		static std::list<void(*)(Key)>		keyPressHandlers;
		static std::list<void(*)(Key)>		keyReleaseHandlers;
		static std::list<void(*)(Key)>		keyClickHandlers;
		static std::list<void(*)(Button)>	mousePressHandlers;
		static std::list<void(*)(Button)>	mouseReleaseHandlers;
		static std::list<void(*)(Button)>	mouseClickHandlers;
		static std::list<void(*)(int, int)>	mouseMoveHandlers;
		static std::list<void(*)(int, int)>	resizeHandlers;
		static std::list<InputEvents*>		handlers;
		
		static Key lastKey;
		static Button lastButton;
		static Vector2 lastMousePos;
		
		static void init();
		
		static void onKeyPressed		(sf::Event event);
		static void onKeyReleased		(sf::Event event);
		static void onMousePressed		(sf::Event event);
		static void onMouseReleased		(sf::Event event);
		static void onMouseMoved		(sf::Event event);
		static void onResized			(sf::Event event);
	};
	
	class InputEvents {
	public:
		InputEvents() { Input::registerHandler(this); }
		
		virtual void onKeyPress		(Input::Key key) {}
		virtual void onKeyRelease	(Input::Key key) {}
		virtual void onKeyClick		(Input::Key key) {}
		virtual void onMousePress	(Input::Button button) {}
		virtual void onMouseRelease	(Input::Button button) {}
		virtual void onMouseClick	(Input::Button button) {}
		virtual void onMouseMove	(int x, int y) {}
		virtual void onResize		(int x, int y) {}
		
		virtual ~InputEvents() { Input::unregisterHandler(this); }
	};
}
