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
