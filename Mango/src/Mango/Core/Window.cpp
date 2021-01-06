#include "MangoPCH.h"
#include "Window.h"

#ifdef MANGO_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"	
#endif

namespace Mango {
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef MANGO_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		MGO_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}