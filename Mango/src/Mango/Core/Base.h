#pragma once
#include <memory>
#include <filesystem>

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
	#if defined(MANGO_PLATFORM_WINDOWS)
		#define __MGO_DEBUGBREAK() __debugbreak()
	#elif defined(MANGO_PLATFORM_LINUX)
		#include <signal.h>
		#define __MGO_DEBUGBREAK() raise(SIGTRAP)
	#else
		#define __MGO_DEBUGBREAK()
		//#error "Platform doesn't support debugbreak yet!"
	#endif
	#define MANGO_ENABLE_ASSERTS
#else
	#define __MGO_DEBUGBREAK()
#endif

#define __MGO_EXPAND_MACRO(x) x
#define __MGO_STRINGIFY_MACRO(x) #x

#ifdef MANGO_ENABLE_ASSERTS

	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define __MGO_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { MGO##type##ERROR(msg, __VA_ARGS__); __MGO_DEBUGBREAK(); } }
	#define __MGO_ASSERT_WITH_MSG(type, check, ...) __MGO_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define __MGO_ASSERT_NO_MSG(type, check) __MGO_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", __MGO_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define __MGO_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define __MGO_ASSERT_GET_MACRO(...) __MGO_EXPAND_MACRO( __MGO_ASSERT_GET_MACRO_NAME(__VA_ARGS__, __MGO_ASSERT_WITH_MSG, __MGO_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define MGO_ASSERT(...) __MGO_EXPAND_MACRO( __MGO_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define MGO_CORE_ASSERT(...) __MGO_EXPAND_MACRO( __MGO_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )

	//#define MGO_ASSERT(X, ...) { if (!(X)) { MGO_ERROR("Assertion failed: {0}", __VA_ARGS__); __MGO_DEBUGBREAK(); } }
	//#define MGO_CORE_ASSERT(X, ...) { if (!(X)) { MGO_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __MGO_DEBUGBREAK(); } }
#else
	#define MGO_ASSERT(...) 
	#define MGO_CORE_ASSERT(...) 
#endif

#define BIT(x) (1 << (x))

#define MGO_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }


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
