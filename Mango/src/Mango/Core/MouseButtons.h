#pragma once


namespace Mango {
	typedef enum class MouseButton : uint16_t
	{
		Button1 = 0,
		Button2 = 1,
		Button3 = 2,
		Button4 = 3, 
		Button5 = 4,
		Button6 = 5,
		Button7 = 6,
		Button8 = 7,

		Last = Button8,
		Left = Button1,
		Right = Button2,
		Middle = Button3,
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseButton mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

// From glfw3.h
#define MGO_MOUSE_BUTTON_1         ::Mango::MouseButton::Button1
#define MGO_MOUSE_BUTTON_2         ::Mango::MouseButton::Button2
#define MGO_MOUSE_BUTTON_3         ::Mango::MouseButton::Button3
#define MGO_MOUSE_BUTTON_4         ::Mango::MouseButton::Button4
#define MGO_MOUSE_BUTTON_5         ::Mango::MouseButton::Button5
#define MGO_MOUSE_BUTTON_6         ::Mango::MouseButton::Button6
#define MGO_MOUSE_BUTTON_7         ::Mango::MouseButton::Button7
#define MGO_MOUSE_BUTTON_8         ::Mango::MouseButton::Button8
#define MGO_MOUSE_BUTTON_LAST      ::Mango::MouseButton::Last
#define MGO_MOUSE_BUTTON_LEFT      ::Mango::MouseButton::Left
#define MGO_MOUSE_BUTTON_RIGHT     ::Mango::MouseButton::Right
#define MGO_MOUSE_BUTTON_MIDDLE    ::Mango::MouseButton::Middle
