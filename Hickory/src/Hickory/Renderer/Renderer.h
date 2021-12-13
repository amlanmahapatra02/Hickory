#pragma once

#include "RenderCommand.h"

#include "Camera.h"
#include "Shader.h"

namespace Hickory
{
	class Renderer
	{
		public:
			static void BeginScene(Camera& camera);
			static void EndScene();

			static void Submit(const std::shared_ptr<Shader>& shader,const std::shared_ptr<VertexArray>& vertexArray);

			inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		private:
			struct SceneData
			{
				glm::mat4 ViewPorojectionMatrix;
			};

			static SceneData* m_SceneData;
	};
}