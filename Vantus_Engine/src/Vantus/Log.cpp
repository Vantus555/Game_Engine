#include "vpch.h"
#include "Log.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Vantus {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_st("Vantus");
		s_ClientLogger = spdlog::stdout_color_st("APP");
	}
	std::shared_ptr<spdlog::logger>& Log::GetCoreLogger() { return s_CoreLogger; }
	std::shared_ptr<spdlog::logger>& Log::GetClientLogger() { return s_ClientLogger; }
}
