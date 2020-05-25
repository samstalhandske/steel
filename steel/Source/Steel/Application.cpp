#include "pch.h"
#include "Application.hpp"

#include "Steel/Debug/Log.hpp"

#include <glad/glad.h>


namespace Steel
{
	Application* Application::myInstance = nullptr;

	Application::Application()
	{
		STEEL_ENGINE_ASSERT(!myInstance, "Instance of Application already exists! There can only be one!");
		myInstance = this;

		myWindow = std::unique_ptr<Window>(Window::Create());
		myWindow->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		unsigned int id;
		glGenVertexArrays(1, &id);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (myIsRunning)
		{
			glClearColor(std::clamp(std::sin(val), 0.0f, 1.0f), std::sin(val + 0.2f), std::sin(val - 0.1f), 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			val += 0.01f;


			for (Layer* layer : myLayerStack)
			{
				layer->OnUpdate();
			}

			myWindow->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(Application::OnMouseScrolled));

		//STEEL_ENGINE_TRACE("{0}", e);

		for (auto it = myLayerStack.end(); it != myLayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}

	}

	void Application::PushLayer(Layer* aLayer)
	{
		myLayerStack.PushLayer(aLayer);
		aLayer->OnAttach();
	}

	void Application::PushOverlay(Layer* aLayer)
	{
		myLayerStack.PushOverlay(aLayer);
		aLayer->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		myIsRunning = false;

		return true;
	}

	bool Application::OnMouseScrolled(MouseScrolledEvent& e)
	{

		return false;
	}
}
