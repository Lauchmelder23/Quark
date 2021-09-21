#pragma once

#ifdef QK_PLATFORM_WINDOWS
	#ifdef QK_BUILD_DLL
		#define QUARK_API __declspec(dllexport)
	#else 
		#define QUARK_API __declspec(dllimport)
	#endif // QK_BUILD_DLL
#else 
	#error Quark only supports Windows
#endif // QK_PLATFORM_WINDOWS

#define BIT(x) (1 << x)
