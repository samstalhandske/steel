#pragma once

#ifdef STEEL_PLATFORM_WINDOWS
	#ifdef STEEL_BUILD_DLL
		#define STEEL_API __declspec(dllexport)
	#else
		#define STEEL_API __declspec(dllimport)
	#endif

#else
	#error Steel Engine is Windows only at the moment...
#endif

#define BIT(x) (1 << x) 