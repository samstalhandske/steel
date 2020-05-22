
#pragma once

#ifdef STEEL_PLATFORM_WINDOWS

extern Steel::Application* Steel::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Steel::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif