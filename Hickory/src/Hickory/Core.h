#pragma once

#ifdef HK_PLATFORM_WINDOWS
	#ifdef HK_BUILD_DLL
		#define HICKORY_API _declspec(dllexport)
	#else
		#define HICKORY_API _declspec(dllimport)

	#endif // DEBUG
#else
	#error Only Supported in Windows only 

#endif // HK_PLATFORM_WINDOWS

#ifdef HK_ENABLE_ASSERTS
#define HK_ASSERT(x, ...) { if(!(x)) { HK_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define HK_CORE_ASSERT(x, ...) { if(!(x)) { HK_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define HK_ASSERT(x, ...)
#define HK_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HK_BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)
