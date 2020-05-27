#pragma once

#include "Core.hpp"
#include "Window.hpp"
#include "Steel/LayerStack.hpp"
#include "Steel/Events/Event.hpp"
#include "Steel/Events/ApplicationEvent.h"
#include "Steel/Events/MouseEvent.hpp"

#include "Steel/ImGui/ImGuiLayer.hpp"

#include "Steel/Renderer/Shader.hpp"
#include "Steel/Renderer/Buffer.hpp"

namespace Steel
{
	class Application
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
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		static Application* myInstance;

		bool myIsRunning = true;
		
		ImGuiLayer* myImGuiLayer;
		LayerStack myLayerStack;

		UINT myVertexArray;
		
		std::unique_ptr<Window> myWindow;

		std::unique_ptr<Shader> myShader;
		std::unique_ptr<VertexBuffer> myVertexBuffer;
		std::unique_ptr<IndexBuffer> myIndexBuffer;

	};

	Application* CreateApplication();
}