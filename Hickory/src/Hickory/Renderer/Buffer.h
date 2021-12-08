#pragma once
#include <vector>

namespace Hickory
{

	enum class ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType Type)
	{
		switch (Type)
		{
			case Hickory::ShaderDataType::None:			return 4;
			case Hickory::ShaderDataType::Float:		return 4;
			case Hickory::ShaderDataType::Float2:		return 4 * 2;
			case Hickory::ShaderDataType::Float3:		return 4 * 3;
			case Hickory::ShaderDataType::Float4:		return 4 * 4;
			case Hickory::ShaderDataType::Mat3:			return 4 * 3 * 3;
			case Hickory::ShaderDataType::Mat4:			return 4 * 4 * 4;
			case Hickory::ShaderDataType::Int:			return 4;
			case Hickory::ShaderDataType::Int2:			return 4 * 2;
			case Hickory::ShaderDataType::Int3:			return 4 * 3;
			case Hickory::ShaderDataType::Int4:			return 4 * 4;
			case Hickory::ShaderDataType::Bool:			return 1;
		
		}

		HK_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement() {};

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			:Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case Hickory::ShaderDataType::Float:		return 1;
				case Hickory::ShaderDataType::Float2:		return 2;
				case Hickory::ShaderDataType::Float3:		return 3;
				case Hickory::ShaderDataType::Float4:		return 4;
				case Hickory::ShaderDataType::Mat3:			return 3 * 3;
				case Hickory::ShaderDataType::Mat4:			return 4 * 4;
				case Hickory::ShaderDataType::Int:			return 1;
				case Hickory::ShaderDataType::Int2:			return 2;
				case Hickory::ShaderDataType::Int3:			return 3;
				case Hickory::ShaderDataType::Int4:			return 4;
				case Hickory::ShaderDataType::Bool:			return 1;

			}

			HK_CORE_ASSERT(false, "Unknown ShaderDataType");
			return 0;
		}
	};

	class BufferLayout
	{
		public:
			BufferLayout() {}

			BufferLayout(const std::initializer_list<BufferElement>& element)
				:m_Element(element)
			{
				CalculateOffsetsAndStride();
			}

			inline uint32_t GetStride() const { return m_Stride; }
			inline const std::vector<BufferElement>& GetElement() const { return m_Element; }

			std::vector<BufferElement>::iterator begin() { return m_Element.begin(); }
			std::vector<BufferElement>::iterator end() { return m_Element.end(); }

			//optional
			std::vector<BufferElement>::const_iterator begin() const { return m_Element.begin(); }
			std::vector<BufferElement>::const_iterator end() const { return m_Element.end(); }

		private:
			void CalculateOffsetsAndStride()
			{
				uint32_t offset = 0;
				m_Stride = 0;

				//This automatically calculate all the offset and stride
				for (auto& element : m_Element)
				{
					element.Offset = offset;
					offset += element.Size;
					m_Stride += element.Size;
				}
			}

		private:
			std::vector<BufferElement> m_Element;
			uint32_t m_Stride = 0;
	};


	class VertexBuffer
	{
		public:
			virtual ~VertexBuffer() {}

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			virtual const BufferLayout& GetLayout() const = 0;
			virtual void SetLayout(const BufferLayout& layout) = 0;

			static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
		public:
			virtual ~IndexBuffer() {}

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			virtual uint32_t GetCount() const = 0;

			static IndexBuffer* Create(uint32_t* indices, uint32_t size);

	};
}