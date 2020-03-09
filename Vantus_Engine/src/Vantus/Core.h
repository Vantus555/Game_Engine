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

#define BIT(x) (1 << x)