#pragma once

#ifdef QK_PLATFORM_WINDOWS
	#ifdef QK_DYNAMIC_LINK
		#ifdef QK_BUILD_DLL
			#define QUARK_API __declspec(dllexport)
		#else 
			#define QUARK_API __declspec(dllimport)
		#endif // QK_BUILD_DLL
	#else
		#define QUARK_API
	#endif
#else 
	#error Quark only supports Windows
#endif // QK_PLATFORM_WINDOWS

#ifdef QK_ENABLE_ASSERTS
	#define QK_ASSERT(x, ...) { if(!(x)) { QK_FATAL("Assertion Failed in file {0}:{1} -> {2}", __FILE__, __LINE__, __VA_ARGS__); __debugbreak(); }}
	#define QK_CORE_ASSERT(x, ...) { if(!(x)) { QK_CORE_FATAL("Assertion Failed in file {0}:{1} -> {2}", __FILE__, __LINE__, __VA_ARGS__); __debugbreak(); }}
#else
	#define QK_ASSERT(x, ...)
	#define QK_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define QK_BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)