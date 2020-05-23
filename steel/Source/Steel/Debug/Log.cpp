#include "pch.h"
#include "Log.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Steel
{
	std::shared_ptr<spdlog::logger> Log::myEngineLogger;
	std::shared_ptr<spdlog::logger> Log::myGameLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		myEngineLogger	= spdlog::stdout_color_mt("STEEL");
		myEngineLogger->set_level(spdlog::level::level_enum::trace);
		STEEL_ENGINE_INFO("Initialized successfully!");

		myGameLogger	= spdlog::stdout_color_mt("GAME");
		myGameLogger->set_level(spdlog::level::level_enum::trace);
		STEEL_GAME_INFO("Initialized successfully!");

	}
}

