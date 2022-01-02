#pragma once

#include "Hickory/Renderer/RendererAPI.h"

namespace Hickory
{
	class OpenGlRenderAPI : public RendererAPI
	{
		public:

			virtual void SetClearColor(const glm::vec4& color) override;
			virtual void Clear() override;

			virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}