#include "hkpch.h"
#include "VertexArray.h"

#include "Hickory/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hickory
{

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:		HK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		}

		HK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}