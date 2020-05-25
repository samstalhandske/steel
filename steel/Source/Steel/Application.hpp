#pragma once

#include "Core.hpp"
#include "Window.hpp"
#include "Steel/LayerStack.hpp"
#include "Steel/Events/Event.hpp"
#include "Steel/Events/ApplicationEvent.h"
#include "Steel/Events/MouseEvent.hpp"

namespace Steel
{
	class STEEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		inline static Application& GetInstance() { return *myInstance; }

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* aLayer);
		void PushOverlay(Layer* aLayer);

		inline Window& GetWindow() { return *myWindow; }

	private:
		static Application* myInstance;

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);

		bool myIsRunning = true;
		float val = 0.0f;

		LayerStack myLayerStack;

		std::unique_ptr<Window> myWindow;
	};

	Application* CreateApplication();
}