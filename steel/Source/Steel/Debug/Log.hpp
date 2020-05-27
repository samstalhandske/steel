
#pragma once

#include "Steel/Core.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Steel
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger()	{ return myEngineLogger;	}
		inline static std::shared_ptr<spdlog::logger>& GetGameLogger()		{ return myGameLogger;		}

	private:
		static std::shared_ptr<spdlog::logger> myEngineLogger;
		static std::shared_ptr<spdlog::logger> myGameLogger;
	};
}

#pragma region Log Defines

#define STEEL_ENGINE_ERROR(...)		::Steel::Log::GetEngineLogger()->error(__VA_ARGS__)
#define STEEL_ENGINE_WARN(...)		::Steel::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define STEEL_ENGINE_INFO(...)		::Steel::Log::GetEngineLogger()->info(__VA_ARGS__)
#define STEEL_ENGINE_TRACE(...)		::Steel::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define STEEL_ENGINE_CRITICAL(...)	::Steel::Log::GetEngineLogger()->critical(__VA_ARGS__)

#define STEEL_GAME_ERROR(...)		::Steel::Log::GetGameLogger()->error(__VA_ARGS__)
#define STEEL_GAME_WARN(...)		::Steel::Log::GetGameLogger()->warn(__VA_ARGS__)
#define STEEL_GAME_INFO(...)		::Steel::Log::GetGameLogger()->info(__VA_ARGS__)
#define STEEL_GAME_TRACE(...)		::Steel::Log::GetGameLogger()->trace(__VA_ARGS__)
#define STEEL_GAME_CRITICAL(...)	::Steel::Log::GetGameLogger()->critical(__VA_ARGS__)

#pragma endregion

//#ifdef _RETAIL
//#define STEEL_ENGINE_ERROR
//#define STEEL_ENGINE_WARN
//#define STEEL_ENGINE_INFO
//#define STEEL_ENGINE_TRACE
//#define STEEL_ENGINE_CRITICAL
//
//#define STEEL_GAME_ERROR
//#define STEEL_GAME_WARN	
//#define STEEL_GAME_INFO
//#define STEEL_GAME_TRACE	
//#define STEEL_GAME_CRITICAL
//#endif
