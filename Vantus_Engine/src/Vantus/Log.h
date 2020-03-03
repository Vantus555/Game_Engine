#pragma once

#include "memory"
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Vantus {
	class VANTUS_API Log {
	public:
		static void Init();
		
		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger;  }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		spdlog::register_logger(s_CoreLogger);

		s_CoreLogger = spdlog::get("Vantus");
		//s_CoreLogger = spdlog::default_logger();
		s_CoreLogger->set_level(spdlog::level::trace);

		spdlog::register_logger(s_ClientLogger);
		s_ClientLogger = spdlog::get("APP");
		//s_ClientLogger = spdlog::default_logger();
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}

