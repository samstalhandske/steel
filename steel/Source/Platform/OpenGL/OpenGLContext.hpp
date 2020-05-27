
#pragma once

#include "Steel/Renderer/GraphicsContext.hpp"

struct GLFWwindow;

namespace Steel
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* aWindowHandle);
		~OpenGLContext();

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* myWindowHandle;

	};
}
