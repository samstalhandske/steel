#pragma once

#ifdef STEEL_PLATFORM_WINDOWS
	
	#ifdef STEEL_DEBUG
		#define STEEL_ENABLE_ASSERTS
	#endif

	#ifdef STEEL_ENABLE_ASSERTS
		#define STEEL_ASSERT(x, ...) { if(!(x)) { STEEL_GAME_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
		#define STEEL_ENGINE_ASSERT(x, ...) { if(!(x)) { STEEL_ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#else
		#define STEEL_ASSERT(x, ...)
		#define STEEL_ENGINE_ASSERT(x, ...)
	#endif
#else
	#error Steel Engine is Windows only at the moment...
#endif

#define BIT(x) (1 << x) 
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
