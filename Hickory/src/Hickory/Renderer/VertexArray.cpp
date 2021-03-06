#include "hkpch.h"
#include "VertexArray.h"

#include "Hickory/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hickory
{

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		HK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLVertexArray>();
		}

		HK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}