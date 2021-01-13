#pragma once

#include "Mango/Core/Base.h"
#include "Mango/Core/KeyCodes.h"
#include "Mango/Core/MouseButtons.h"

namespace Mango {
	
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode keycode);
		
		static bool IsMouseButtonPressed(MouseButton button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}
