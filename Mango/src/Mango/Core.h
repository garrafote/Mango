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

#ifdef MANGO_ENABLE_ASSERTS
	#define MGO_ASSERT(X, ...) { if (!(X)) { MGO_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define MGO_CORE_ASSERT(X, ...) { if (!(X)) { MGO_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define MGO_ASSERT(X, ...) 
	#define MGO_CORE_ASSERT(X, ...) 
#endif

#define BIT(x) (1 << (x))

#define MGO_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
