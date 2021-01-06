#pragma once

namespace Mango {
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space              = 32,
		Apostrophe         = 39,  /* ' */
		Comma              = 44,  /* , */
		Minus              = 45,  /* - */
		Period             = 46,  /* . */
		Slash              = 47,  /* / */
		Alpha0             = 48,
		Alpha1             = 49,
		Alpha2             = 50,
		Alpha3             = 51,
		Alpha4             = 52,
		Alpha5             = 53,
		Alpha6             = 54,
		Alpha7             = 55,
		Alpha8             = 56,
		Alpha9             = 57,
		Semicolon          = 59,  /* , */
		Equal              = 61,  /* = */
		A                  = 65,
		B                  = 66,
		C                  = 67,
		D                  = 68,
		E                  = 69,
		F                  = 70,
		G                  = 71,
		H                  = 72,
		I                  = 73,
		J                  = 74,
		K                  = 75,
		L                  = 76,
		M                  = 77,
		N                  = 78,
		O                  = 79,
		P                  = 80,
		Q                  = 81,
		R                  = 82,
		S                  = 83,
		T                  = 84,
		U                  = 85,
		V                  = 86,
		W                  = 87,
		X                  = 88,
		Y                  = 89,
		Z                  = 90,
		LeftBracket        = 91,  /* [ */
		Backslash          = 92,  /* \ */
		RightBracket       = 93,  /* ] */
		GraveAccent        = 96,  /* ` */
		World1             = 161, /* non-US #1 */
		World2             = 162, /* non-US #2 */

/* Function keys */
		Escape             = 256,
		Enter              = 257,
		Tab                = 258,
		Backspace          = 259,
		Insert             = 260,
		Delete             = 261,
		RightArrow         = 262,
		LeftArrow          = 263,
		DownArrow          = 264,
		UpArrow            = 265,
		PageUp             = 266,
		PageDown           = 267,
		Home               = 268,
		End                = 269,
		CapsLock           = 280,
		ScorllLock         = 281,
		NumLock            = 282,
		PrintScreen        = 283,
		Pause              = 284,
		F1                 = 290,
		F2                 = 291,
		F3                 = 292,
		F4                 = 293,
		F5                 = 294,
		F6                 = 295,
		F7                 = 296,
		F8                 = 297,
		F9                 = 298,
		F10                = 299,
		F11                = 300,
		F12                = 301,
		F13                = 302,
		F14                = 303,
		F15                = 304,
		F16                = 305,
		F17                = 306,
		F18                = 307,
		F19                = 308,
		F20                = 309,
		F21                = 310,
		F22                = 311,
		F23                = 312,
		F24                = 313,
		F25                = 314,

		KeyPad0            = 320,
		KeyPad1            = 321,
		KeyPad2            = 322,
		KeyPad3            = 323,
		KeyPad4            = 324,
		KeyPad5            = 325,
		KeyPad6            = 326,
		KeyPad7            = 327,
		KeyPad8            = 328,
		KeyPad9            = 329,
		KeyPadDecimal      = 330,
		KeyPadDivide       = 331,
		KeyPadMultiply     = 332,
		KeyPadSubstract    = 333,
		KeyPadAdd          = 334,
		KeyPadEnter        = 335,
		KeyPadEqual        = 336,

		LeftShift          = 340,
		LeftControl        = 341,
		LeftAlt            = 342,
		LeftSuper          = 343,
		RightShift         = 344,
		RightControl       = 345,
		RightAlt           = 346,
		RightSuper         = 347,
		Menu               = 348,

	} KeyCode;
	
	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

#define MGO_KEY_SPACE              ::Mango::KeyCode::Space
#define MGO_KEY_APOSTROPHE         ::Mango::KeyCode::Apostrophe  /* ' */
#define MGO_KEY_COMMA              ::Mango::KeyCode::Comma  /* , */
#define MGO_KEY_MINUS              ::Mango::KeyCode::Minus  /* - */
#define MGO_KEY_PERIOD             ::Mango::KeyCode::Period  /* . */
#define MGO_KEY_SLASH              ::Mango::KeyCode::Slash  /* / */
#define MGO_KEY_0                  ::Mango::KeyCode::Alpha0
#define MGO_KEY_1                  ::Mango::KeyCode::Alpha1
#define MGO_KEY_2                  ::Mango::KeyCode::Alpha2
#define MGO_KEY_3                  ::Mango::KeyCode::Alpha3
#define MGO_KEY_4                  ::Mango::KeyCode::Alpha4
#define MGO_KEY_5                  ::Mango::KeyCode::Alpha5
#define MGO_KEY_6                  ::Mango::KeyCode::Alpha6
#define MGO_KEY_7                  ::Mango::KeyCode::Alpha7
#define MGO_KEY_8                  ::Mango::KeyCode::Alpha8
#define MGO_KEY_9                  ::Mango::KeyCode::Alpha9
#define MGO_KEY_SEMICOLON          ::Mango::KeyCode::Semicolon  /* ; */
#define MGO_KEY_EQUAL              ::Mango::KeyCode::Equal  /* = */
#define MGO_KEY_A                  ::Mango::KeyCode::A
#define MGO_KEY_B                  ::Mango::KeyCode::B
#define MGO_KEY_C                  ::Mango::KeyCode::C
#define MGO_KEY_D                  ::Mango::KeyCode::D
#define MGO_KEY_E                  ::Mango::KeyCode::E
#define MGO_KEY_F                  ::Mango::KeyCode::F
#define MGO_KEY_G                  ::Mango::KeyCode::G
#define MGO_KEY_H                  ::Mango::KeyCode::H
#define MGO_KEY_I                  ::Mango::KeyCode::I
#define MGO_KEY_J                  ::Mango::KeyCode::J
#define MGO_KEY_K                  ::Mango::KeyCode::K
#define MGO_KEY_L                  ::Mango::KeyCode::L
#define MGO_KEY_M                  ::Mango::KeyCode::M
#define MGO_KEY_N                  ::Mango::KeyCode::N
#define MGO_KEY_O                  ::Mango::KeyCode::O
#define MGO_KEY_P                  ::Mango::KeyCode::P
#define MGO_KEY_Q                  ::Mango::KeyCode::Q
#define MGO_KEY_R                  ::Mango::KeyCode::R
#define MGO_KEY_S                  ::Mango::KeyCode::S
#define MGO_KEY_T                  ::Mango::KeyCode::T
#define MGO_KEY_U                  ::Mango::KeyCode::U
#define MGO_KEY_V                  ::Mango::KeyCode::V
#define MGO_KEY_W                  ::Mango::KeyCode::W
#define MGO_KEY_X                  ::Mango::KeyCode::X
#define MGO_KEY_Y                  ::Mango::KeyCode::Y
#define MGO_KEY_Z                  ::Mango::KeyCode::Z
#define MGO_KEY_LEFT_BRACKET       ::Mango::KeyCode::LeftBracket  /* [ */
#define MGO_KEY_BACKSLASH          ::Mango::KeyCode::Backslash  /* \ */
#define MGO_KEY_RIGHT_BRACKET      ::Mango::KeyCode::RightBracket  /* ] */
#define MGO_KEY_GRAVE_ACCENT       ::Mango::KeyCode::GraveAccent  /* ` */
#define MGO_KEY_WORLD_1            ::Mango::KeyCode::World1 /* non-US #1 */
#define MGO_KEY_WORLD_2            ::Mango::KeyCode::World2 /* non-US #2 */

/* Function keys */
#define MGO_KEY_ESCAPE             ::Mango::KeyCode::Escape
#define MGO_KEY_ENTER              ::Mango::KeyCode::Enter
#define MGO_KEY_TAB                ::Mango::KeyCode::Tab
#define MGO_KEY_BACKSPACE          ::Mango::KeyCode::Backspace
#define MGO_KEY_INSERT             ::Mango::KeyCode::Insert
#define MGO_KEY_DELETE             ::Mango::KeyCode::Delete
#define MGO_KEY_RIGHT              ::Mango::KeyCode::RightArrow
#define MGO_KEY_LEFT               ::Mango::KeyCode::LeftArrow
#define MGO_KEY_DOWN               ::Mango::KeyCode::DownArrow
#define MGO_KEY_UP                 ::Mango::KeyCode::UpArrow
#define MGO_KEY_PAGE_UP            ::Mango::KeyCode::PageUp
#define MGO_KEY_PAGE_DOWN          ::Mango::KeyCode::PageDown
#define MGO_KEY_HOME               ::Mango::KeyCode::Home
#define MGO_KEY_END                ::Mango::KeyCode::End
#define MGO_KEY_CAPS_LOCK          ::Mango::KeyCode::CapsLock
#define MGO_KEY_SCROLL_LOCK        ::Mango::KeyCode::ScorllLock
#define MGO_KEY_NUM_LOCK           ::Mango::KeyCode::NumLock
#define MGO_KEY_PRINT_SCREEN       ::Mango::KeyCode::PrintScreen
#define MGO_KEY_PAUSE              ::Mango::KeyCode::Pause
#define MGO_KEY_F1                 ::Mango::KeyCode::F1
#define MGO_KEY_F2                 ::Mango::KeyCode::F2
#define MGO_KEY_F3                 ::Mango::KeyCode::F3
#define MGO_KEY_F4                 ::Mango::KeyCode::F4
#define MGO_KEY_F5                 ::Mango::KeyCode::F5
#define MGO_KEY_F6                 ::Mango::KeyCode::F6
#define MGO_KEY_F7                 ::Mango::KeyCode::F7
#define MGO_KEY_F8                 ::Mango::KeyCode::F8
#define MGO_KEY_F9                 ::Mango::KeyCode::F9
#define MGO_KEY_F10                ::Mango::KeyCode::F10
#define MGO_KEY_F11                ::Mango::KeyCode::F11
#define MGO_KEY_F12                ::Mango::KeyCode::F12
#define MGO_KEY_F13                ::Mango::KeyCode::F13
#define MGO_KEY_F14                ::Mango::KeyCode::F14
#define MGO_KEY_F15                ::Mango::KeyCode::F15
#define MGO_KEY_F16                ::Mango::KeyCode::F16
#define MGO_KEY_F17                ::Mango::KeyCode::F17
#define MGO_KEY_F18                ::Mango::KeyCode::F18
#define MGO_KEY_F19                ::Mango::KeyCode::F19
#define MGO_KEY_F20                ::Mango::KeyCode::F20
#define MGO_KEY_F21                ::Mango::KeyCode::F21
#define MGO_KEY_F22                ::Mango::KeyCode::F22
#define MGO_KEY_F23                ::Mango::KeyCode::F23
#define MGO_KEY_F24                ::Mango::KeyCode::F24
#define MGO_KEY_F25                ::Mango::KeyCode::F25
#define MGO_KEY_KP_0               ::Mango::KeyCode::KeyPad0
#define MGO_KEY_KP_1               ::Mango::KeyCode::KeyPad1
#define MGO_KEY_KP_2               ::Mango::KeyCode::KeyPad2
#define MGO_KEY_KP_3               ::Mango::KeyCode::KeyPad3
#define MGO_KEY_KP_4               ::Mango::KeyCode::KeyPad4
#define MGO_KEY_KP_5               ::Mango::KeyCode::KeyPad5
#define MGO_KEY_KP_6               ::Mango::KeyCode::KeyPad6
#define MGO_KEY_KP_7               ::Mango::KeyCode::KeyPad7
#define MGO_KEY_KP_8               ::Mango::KeyCode::KeyPad8
#define MGO_KEY_KP_9               ::Mango::KeyCode::KeyPad9
#define MGO_KEY_KP_DECIMAL         ::Mango::KeyCode::KeyPadDecimal
#define MGO_KEY_KP_DIVIDE          ::Mango::KeyCode::KeyPadDivide
#define MGO_KEY_KP_MULTIPLY        ::Mango::KeyCode::KeyPadMultiply
#define MGO_KEY_KP_SUBTRACT        ::Mango::KeyCode::KeyPadSubstract
#define MGO_KEY_KP_ADD             ::Mango::KeyCode::KeyPadAdd
#define MGO_KEY_KP_ENTER           ::Mango::KeyCode::KeyPadEnter
#define MGO_KEY_KP_EQUAL           ::Mango::KeyCode::KeyPadEqual
#define MGO_KEY_LEFT_SHIFT         ::Mango::KeyCode::LeftShift
#define MGO_KEY_LEFT_CONTROL       ::Mango::KeyCode::LeftControl
#define MGO_KEY_LEFT_ALT           ::Mango::KeyCode::LeftAlt
#define MGO_KEY_LEFT_SUPER         ::Mango::KeyCode::LeftSuper
#define MGO_KEY_RIGHT_SHIFT        ::Mango::KeyCode::RightShift
#define MGO_KEY_RIGHT_CONTROL      ::Mango::KeyCode::RightControl
#define MGO_KEY_RIGHT_ALT          ::Mango::KeyCode::RightAlt
#define MGO_KEY_RIGHT_SUPER        ::Mango::KeyCode::RightSuper
#define MGO_KEY_MENU               ::Mango::KeyCode::Menu

