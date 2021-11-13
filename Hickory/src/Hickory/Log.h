#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Hickory
{	
	class HICKORY_API Log
	{
		public:
			static void Init();

			inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
			inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		protected:
			static std::shared_ptr<spdlog::logger> s_CoreLogger;
			static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core Log Macro
#define HK_CORE_TRACE(...)		::Hickory::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HK_CORE_INFO(...)		::Hickory::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HK_CORE_WARN(...)		::Hickory::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HK_CORE_ERROR(...)		::Hickory::Log::GetCoreLogger()->error(__VA_ARGS__)

//Client Log Macro
#define HK_TRACE(...)			::Hickory::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HK_INFO(...)			::Hickory::Log::GetClientLogger()->info(__VA_ARGS__)
#define HK_WARN(...)			::Hickory::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HK_ERROR(...)			::Hickory::Log::GetClientLogger()->error(__VA_ARGS__)