#include "pch.h"
#include "Buffer.hpp"

#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLBuffer.hpp"

namespace Steel
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:		STEEL_ENGINE_ASSERT(false, "Renderer API is set to None!"); break;
			case RendererAPI::OpenGL:	return new OpenGLVertexBuffer(vertices, size); break;
		}

		STEEL_ENGINE_ASSERT(false, "Renderer API invalid!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:		STEEL_ENGINE_ASSERT(false, "Renderer API is set to None!"); break;
			case RendererAPI::OpenGL:	return new OpenGLIndexBuffer(indices, count); break;
		}

		STEEL_ENGINE_ASSERT(false, "Renderer API invalid!");
		return nullptr;
	}
}
