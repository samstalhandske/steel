#include "pch.h"
#include "Application.hpp"

#include "Steel/Debug/Log.hpp"

#include <glad/glad.h>

#include "Input.hpp"

namespace Steel
{
	Application* Application::myInstance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType aType)
	{
		switch (aType)
		{
		case Steel::ShaderDataType::Float:	return GL_FLOAT;
		case Steel::ShaderDataType::Float2: return GL_FLOAT;
		case Steel::ShaderDataType::Float3: return GL_FLOAT;
		case Steel::ShaderDataType::Float4: return GL_FLOAT;
		case Steel::ShaderDataType::Mat3:   return GL_FLOAT;
		case Steel::ShaderDataType::Mat4:	return GL_FLOAT;
		case Steel::ShaderDataType::Int:	return GL_INT;
		case Steel::ShaderDataType::Int2:	return GL_INT;
		case Steel::ShaderDataType::Int3:	return GL_INT;
		case Steel::ShaderDataType::Int4:	return GL_INT;
		case Steel::ShaderDataType::Bool:	return GL_BOOL;
		}

		STEEL_ENGINE_ASSERT(false, "Failed converting shader data type to opengl");
		return 0;
	}


	Application::Application()
	{
		STEEL_ENGINE_ASSERT(!myInstance, "Instance of Application already exists! There can only be one!");
		myInstance = this;

		myWindow = std::unique_ptr<Window>(Window::Create());
		myWindow->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		myImGuiLayer = new ImGuiLayer();
		PushOverlay(myImGuiLayer);


		glGenVertexArrays(1, &myVertexArray);
		glBindVertexArray(myVertexArray);

		float vertices[7 * 3] = {
			-0.5f, -0.5f,  0.0f,	0.0f, 0.5f, 1.0f, 1.0f,
			 0.5f, -0.5f,  0.0f,	0.5f, 0.8f, 0.7f, 1.0f,
			 0.0f,  0.5f,  0.0f,	1.f, 0.9f, 0.5f, 1.0f
		};

		myVertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "position" },
			{ ShaderDataType::Float4, "color" }

		};

		myVertexBuffer->SetLayout(layout);

		uint32_t index = 0;
		for (auto& element : myVertexBuffer->GetLayout().GetElements())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.type),
				(element.normalized ? GL_TRUE : GL_FALSE),
				layout.GetStride(),
				(const void*)element.offset);

			index++;
		}

		uint32_t indices[3] = { 0, 1, 2 };
		myIndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
			   
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 position;
			layout(location = 1) in vec4 color;

			out vec3 v_Position;			
			out vec4 v_Color;			
			
			void main()
			{
				v_Position = position;
				v_Color = color;
				gl_Position = vec4(position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}	
		)";

		myShader.reset(new Shader(vertexSrc, fragmentSrc));


		STEEL_ENGINE_INFO("Application initialized!");

	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (myIsRunning)
		{
			glClearColor(0.117f, 0.247f, 0.35f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			myShader->Bind();
			glBindVertexArray(myVertexArray);
			glDrawElements(GL_TRIANGLES, myIndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : myLayerStack)
			{
				layer->OnUpdate();
			}

			myImGuiLayer->Begin();
			for (Layer* layer : myLayerStack)
				layer->OnImGuiRender();
			myImGuiLayer->End();

			myWindow->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

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
}
