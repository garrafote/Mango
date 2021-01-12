#pragma once

#include "Mango/Core/Base.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Mango {

	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros

#define MGO_CORE_TRACE(...)     ::Mango::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MGO_CORE_INFO(...)      ::Mango::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MGO_CORE_WARN(...)      ::Mango::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MGO_CORE_ERROR(...)     ::Mango::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MGO_CORE_CRITICAL(...)  ::Mango::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros

#define MGO_TRACE(...)          ::Mango::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MGO_INFO(...)           ::Mango::Log::GetClientLogger()->info(__VA_ARGS__)
#define MGO_WARN(...)           ::Mango::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MGO_ERROR(...)          ::Mango::Log::GetClientLogger()->error(__VA_ARGS__)
#define MGO_CRITICAL(...)       ::Mango::Log::GetClientLogger()->critical(__VA_ARGS__)
