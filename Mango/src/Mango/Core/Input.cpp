#include "MangoPCH.h"
#include "Input.h"

#ifdef MANGO_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
#endif

namespace Mango {
	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
#ifdef MANGO_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
#else
		MGO_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}
