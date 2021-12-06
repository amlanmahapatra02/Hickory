#include "hkpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hickory
{
	///////////////////////////////////////////////
	//VertexBuffer//////////////////////////////////
	///////////////////////////////////////////////

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:		HK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
		}

		HK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	///////////////////////////////////////////////
	//IndexBuffer//////////////////////////////////
	///////////////////////////////////////////////

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:		HK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLIndexBuffer(indices, size);
		}

		HK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}