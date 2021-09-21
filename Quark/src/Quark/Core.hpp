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

#ifdef QK_ENABLE_ASSERTS
	#define QK_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define QK_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define QK_ASSERT(x, ...)
	#define QK_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
