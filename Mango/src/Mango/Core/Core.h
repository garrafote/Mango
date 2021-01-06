#pragma once
#include <memory>

// Platform dettection using predefined macros
#ifdef _WIN32
	// Windows x64/x86
	#ifdef _WIN64
		#define MANGO_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
	#endif
#elif defined (__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	// TARGET_OS_MAC exists on all the platforms
	// so we must check all of them (in this order)
	// to ensure that we're running on MAC
	// and not some other Apple platform
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "iOS simulator is not supported!"
	#elif TARGET_OS_PHONE == 1
		#define MANGO_PLATFORM_IOS
		#error "iOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define MANGO_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
// We also have to check __ANDROID__ BEFORE __linux__
// since android is based on the linux kernel
// it has __linux__ defined
#elif defined(__ANDROID__)
	#define MANGO_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define MANGO_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	#error "Unknown platform!"
#endif

#ifdef MANGO_DEBUG
	#define MANGO_ENABLE_ASSERTS
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


namespace Mango {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
