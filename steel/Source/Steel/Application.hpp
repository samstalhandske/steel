#pragma once

#include "Core.hpp"
#include "Events/Event.hpp"

namespace Steel
{
	class STEEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}