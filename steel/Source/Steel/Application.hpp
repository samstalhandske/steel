#pragma once

#include "Core.hpp"

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