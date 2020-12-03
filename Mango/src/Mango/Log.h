#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Mango {

	class MANGO_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros

#define MGO_CORE_TRACE(...)   ::Mango::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MGO_CORE_INFO(...)    ::Mango::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MGO_CORE_WARN(...)    ::Mango::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MGO_CORE_ERROR(...)   ::Mango::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MGO_CORE_FATAL(...)   ::Mango::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros

#define MGO_TRACE(...)        ::Mango::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MGO_INFO(...)         ::Mango::Log::GetClientLogger()->info(__VA_ARGS__)
#define MGO_WARN(...)         ::Mango::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MGO_ERROR(...)        ::Mango::Log::GetClientLogger()->error(__VA_ARGS__)
#define MGO_FATAL(...)        ::Mango::Log::GetClientLogger()->fatal(__VA_ARGS__)
