#include <Steel.hpp>

#include "imgui/imgui.h"

class TestLayer : public Steel::Layer
{
public:
	TestLayer() : Layer("Example")
	{
	}

	void OnUpdate() override
	{
	}
	virtual void OnImGuiRender() override
	{
	}
	void OnEvent(Steel::Event& event) override
	{
	}
private:
};

class Test : public Steel::Application
{
public:
	Test()
	{
		PushLayer(new TestLayer());

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