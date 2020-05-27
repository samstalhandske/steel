
#pragma once


namespace Steel
{
	enum class ShaderDataType
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType aType)
	{
		switch (aType)
		{
		case Steel::ShaderDataType::None:	return 0;
		case Steel::ShaderDataType::Float:	return 4;
		case Steel::ShaderDataType::Float2: return 4 * 2;
		case Steel::ShaderDataType::Float3: return 4 * 3;
		case Steel::ShaderDataType::Float4: return 4 * 4;
		case Steel::ShaderDataType::Mat3:	return 4 * 3 * 3;
		case Steel::ShaderDataType::Mat4:	return 4 * 4 * 4;
		case Steel::ShaderDataType::Int:	return 4;
		case Steel::ShaderDataType::Int2:	return 4 * 2;
		case Steel::ShaderDataType::Int3:	return 4 * 3;
		case Steel::ShaderDataType::Int4:	return 4 * 4;
		case Steel::ShaderDataType::Bool:	return 1;
		}

		STEEL_ENGINE_ASSERT(false, "ShaderDataType unknown!");
		return 0;
	}

	struct BufferElement
	{
		std::string name;
		ShaderDataType type;
		uint32_t size;
		uint32_t offset;
		bool normalized;

		BufferElement() = default;

		BufferElement(ShaderDataType aType, const std::string& aName, bool aNormalized = false) :
			name(aName),
			type(aType),
			size(ShaderDataTypeSize(aType)),
			offset(0),
			normalized(aNormalized)
		{

		}

		uint32_t GetComponentCount() const
		{
			switch (type)
			{
			case Steel::ShaderDataType::None:	return 0;
			case Steel::ShaderDataType::Float:	return 1;
			case Steel::ShaderDataType::Float2: return 2;
			case Steel::ShaderDataType::Float3: return 3;
			case Steel::ShaderDataType::Float4: return 4;
			case Steel::ShaderDataType::Mat3:	return 4 * 3;
			case Steel::ShaderDataType::Mat4:	return 4 * 4;
			case Steel::ShaderDataType::Int:	return 1;
			case Steel::ShaderDataType::Int2:	return 2;
			case Steel::ShaderDataType::Int3:	return 3;
			case Steel::ShaderDataType::Int4:	return 4;
			case Steel::ShaderDataType::Bool:	return 1;
			}
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: myElements(elements) 
		{
			CalculateOffsetAndStride();
		}

		inline uint32_t GetStride() const { return myStride; }
		inline const std::vector<BufferElement>& GetElements() const { return myElements; }
	private:
		void CalculateOffsetAndStride()
		{
			uint32_t offset = 0;
			myStride = 0;

			for (auto& element : myElements)
			{
				element.offset = offset;
				offset += element.size;
				myStride += element.size;
			}
		}
	private:
		std::vector<BufferElement> myElements;
		uint32_t myStride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;


		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}