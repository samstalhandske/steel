
#pragma once

#include "Steel/Renderer/Buffer.hpp"

namespace Steel
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { myLayout = layout; }
		virtual const BufferLayout& GetLayout() const override { return myLayout; }

	private:
		uint32_t myRendererID;
		BufferLayout myLayout;
	};


	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const { return myCount; }

	private:
		uint32_t myRendererID;
		uint32_t myCount;
	};
}
