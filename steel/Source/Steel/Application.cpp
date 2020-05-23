#include "pch.h"
#include "Application.hpp"

#include "Steel/Events/ApplicationEvent.h"
#include "Steel/Debug/Log.hpp"

Steel::Application::Application()
{
}

Steel::Application::~Application()
{
}

void Steel::Application::Run()
{
	WindowResizeEvent e(1280, 720);
	if (e.IsInCategory(EventCategoryApplication))
	{
		STEEL_GAME_TRACE(e);
	}
	if (e.IsInCategory(EventCategoryInput))
	{
		STEEL_GAME_TRACE(e);
	}

	while (true);
}
