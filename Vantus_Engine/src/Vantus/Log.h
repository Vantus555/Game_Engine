 #pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Vantus {
	class VANTUS_API Log {
	public:
		static void Init();
		
		static std::shared_ptr<spdlog::logger>& GetCoreLogger();
		static std::shared_ptr<spdlog::logger>& GetClientLogger();
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

	#define VANTUS_CORE_TRACE(...) ::Vantus::Log::GetCoreLogger()->trace(__VA_ARGS__);
	#define VANTUS_CORE_INFO(...) ::Vantus::Log::GetCoreLogger()->info(__VA_ARGS__);
	#define VANTUS_CORE_WARN(...) ::Vantus::Log::GetCoreLogger()->warn(__VA_ARGS__);
	#define VANTUS_CORE_ERROR(...) ::Vantus::Log::GetCoreLogger()->error(__VA_ARGS__);
	#define VANTUS_CORE_CRITICAL(...) ::Vantus::Log::GetCoreLogger()->critical(__VA_ARGS__);

	#define VANTUS_TRACE(...) ::Vantus::Log::GetClientLogger()->trace(__VA_ARGS__);
	#define VANTUS_INFO(...) ::Vantus::Log::GetClientLogger()->info(__VA_ARGS__);
	#define VANTUS_WARN(...) ::Vantus::Log::GetClientLogger()->warn(__VA_ARGS__);
	#define VANTUS_ERROR(...) ::Vantus::Log::GetClientLogger()->error(__VA_ARGS__);
	#define VANTUS_CRITICAL(...) ::Vantus::Log::GetClientLogger()->critical(__VA_ARGS__);
}

