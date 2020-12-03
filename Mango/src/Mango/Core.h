#pragma once

#ifdef MANGO_PLATFORM_WINDOWS
	#ifdef MANGO_BUILD_DLL
		#define MANGO_API __declspec(dllexport)
	#else
		#define MANGO_API __declspec(dllimport)
	#endif
#else
	#error Mango only supports Windows!
#endif
