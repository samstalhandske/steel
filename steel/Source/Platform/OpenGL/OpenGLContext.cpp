
#include "pch.h"
#include "OpenGLContext.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Steel
{
	OpenGLContext::OpenGLContext(GLFWwindow* aWindowHandle)
		: myWindowHandle(aWindowHandle)
	{
		STEEL_ENGINE_ASSERT(myWindowHandle, "OpenGLContext, window handle is null");
	}

	OpenGLContext::~OpenGLContext()
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(myWindowHandle);
		int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		STEEL_ENGINE_ASSERT(gladStatus, "Failed to initialize glad!");

		STEEL_ENGINE_INFO("Renderer: {0}, {1}, {2}", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));


		STEEL_ENGINE_INFO("OpenGL initialized!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(myWindowHandle);
	}
}