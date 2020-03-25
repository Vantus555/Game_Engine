#pragma once

#ifdef VANTUS_PLATFORM_WINDOWS
	#ifdef VANTUS_BUILD_DLL
		#define VANTUS_API __declspec(dllexport)
	#else
		#define VANTUS_API __declspec(dllexport)
	#endif
#else
	#error Vantus only support Windows!
#endif

#ifdef VANTUS_DEBUG
	#define VANTUS_ENABLE_ASSERTS
#endif

#ifdef VANTUS_ENABLE_ASSERTS
	#define VANTUS_ASSERT(x, ...) { if(!(x)) { VANTUS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define VANTUS_CORE_ASSERT(x, ...) { if(!(x)) { VANTUS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define VANTUS_ASSERT(x, ...)
	#define VANTUS_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define VANTUS_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)