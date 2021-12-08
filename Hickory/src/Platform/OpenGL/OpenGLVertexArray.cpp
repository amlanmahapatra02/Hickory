#include "hkpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Hickory
{

	static GLenum ShaderDataToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Hickory::ShaderDataType::Float:		return GL_FLOAT;
		case Hickory::ShaderDataType::Float2:		return GL_FLOAT;
		case Hickory::ShaderDataType::Float3:		return GL_FLOAT;
		case Hickory::ShaderDataType::Float4:		return GL_FLOAT;
		case Hickory::ShaderDataType::Mat3:			return GL_FLOAT;
		case Hickory::ShaderDataType::Mat4:			return GL_FLOAT;
		case Hickory::ShaderDataType::Int:			return GL_INT;
		case Hickory::ShaderDataType::Int2:			return GL_INT;
		case Hickory::ShaderDataType::Int3:			return GL_INT;
		case Hickory::ShaderDataType::Int4:			return GL_INT;
		case Hickory::ShaderDataType::Bool:			return GL_BOOL;
		}
	};

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		HK_CORE_ASSERT(vertexBuffer->GetLayout().GetElement().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset
			);

			index++;
		}

		m_VertexBuffer.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}