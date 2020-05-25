#include "pch.h"
#include <Steel.hpp>

class TestLayer : public Steel::Layer
{
public:
	TestLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		STEEL_GAME_INFO("TestLayer Updating");
	}
	void OnEvent(Steel::Event& event) override
	{
		STEEL_GAME_TRACE("{0}", event);
	}
private:

};

class Test : public Steel::Application
{
public:
	Test()
	{
		PushLayer(new TestLayer());
		PushOverlay(new Steel::ImGuiLayer());

	}
	~Test()
	{

	}
private:

};

Steel::Application* Steel::CreateApplication()
{
	return new Test();
}