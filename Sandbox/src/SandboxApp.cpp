#include <Hickory.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Hickory::Layer
{
	public:
		ExampleLayer()
			:Layer("Example"),m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
		{
			m_VertexArray.reset(Hickory::VertexArray::Create());


			float vertices[3 * 7] = {
				-0.5f, -0.5f, 0.0f,   0.8f, 0.2f, 0.8f, 1.0f,
				 0.5f, -0.5f, 0.0f,	  0.2f, 0.3f, 0.8f, 1.0f,
				 0.0f,	0.5f, 0.0f,	  0.8f, 0.8f, 0.2f, 1.0f,
			};

			Hickory::Ref<Hickory::VertexBuffer> vertexBuffer;

			vertexBuffer.reset(Hickory::VertexBuffer::Create(vertices, sizeof(vertices)));

			Hickory::BufferLayout layout = {
					{Hickory::ShaderDataType::Float3, "a_Position"},
					{Hickory::ShaderDataType::Float4, "a_Color"}
			};

			vertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(vertexBuffer);


			uint32_t indices[3] = { 0, 1, 2 };
			Hickory::Ref<Hickory::IndexBuffer> indexBuffer;
			indexBuffer.reset(Hickory::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
			m_VertexArray->SetIndexBuffer(indexBuffer);

			m_SquareVA.reset(Hickory::VertexArray::Create());

			float squareVertices[5 * 4] = {
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
				 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
				-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
			};

			Hickory::Ref<Hickory::VertexBuffer> squareVB;
			squareVB.reset(Hickory::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
			squareVB->SetLayout({
				{ Hickory::ShaderDataType::Float3, "a_Position" },
				{ Hickory::ShaderDataType::Float2, "a_TexCoord" }
				});
			m_SquareVA->AddVertexBuffer(squareVB);

			uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
			Hickory::Ref<Hickory::IndexBuffer> squareIB;
			squareIB.reset(Hickory::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
			m_SquareVA->SetIndexBuffer(squareIB);


			std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

			std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

			m_Shader = Hickory::Shader::Create("VertexPosColor",vertexSrc, fragmentSrc);


			std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

			std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

			m_FlatColorShader = Hickory::Shader::Create("FlatColor",flatColorShaderVertexSrc, flatColorShaderFragmentSrc);


			auto textureShader = m_ShaderLibrary.Load("Assests/Shaders/Texture.glsl");

			m_Texture = Hickory::Texture2D::Create("Assests/Textures/Checkerboard.png");
			m_LogoTexture = Hickory::Texture2D::Create("Assests/Textures/Twitch_Logo.png");

			std::dynamic_pointer_cast<Hickory::OpenGLShader>(textureShader)->Bind();
			std::dynamic_pointer_cast<Hickory::OpenGLShader>(textureShader)->UploadUniformInt("u_Color", 0);
		}

		void OnUpdate(Hickory::Timestep DeltaTime) override
		{
			//Camera Controls

			if (Hickory::Input::isKeyPressed(HK_KEY_RIGHT) || Hickory::Input::isKeyPressed(HK_KEY_D))
				m_CameraPosition.x += m_CameraMovementSpeed * DeltaTime;

			else if (Hickory::Input::isKeyPressed(HK_KEY_LEFT) || Hickory::Input::isKeyPressed(HK_KEY_A))
					m_CameraPosition.x -= m_CameraMovementSpeed * DeltaTime;

			if (Hickory::Input::isKeyPressed(HK_KEY_UP) || Hickory::Input::isKeyPressed(HK_KEY_W))
				m_CameraPosition.y += m_CameraMovementSpeed * DeltaTime;

			else if (Hickory::Input::isKeyPressed(HK_KEY_DOWN) || Hickory::Input::isKeyPressed(HK_KEY_S))
					m_CameraPosition.y -= m_CameraMovementSpeed * DeltaTime;


			Hickory::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			Hickory::RenderCommand::Clear();

			m_Camera.SetPosition(m_CameraPosition);
			m_Camera.SetRotation(m_CameraRotation);

			Hickory::Renderer::BeginScene(m_Camera);
			

			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

			std::dynamic_pointer_cast<Hickory::OpenGLShader>(m_FlatColorShader)->Bind();
			std::dynamic_pointer_cast<Hickory::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

			for (int y = 0; y < 20; y++)
			{
				for (int x = 0; x < 20; x++)
				{
					glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					Hickory::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
				}
			}

			//Rendering Triangle
			//Hickory::Renderer::Submit(m_Shader, m_VertexArray);

			auto textureShader = m_ShaderLibrary.Get("Texture");

			m_Texture->Bind();
			Hickory::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

			m_LogoTexture->Bind();
			Hickory::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

			Hickory::Renderer::EndScene();
		}

		virtual void OnImGuiRender() override
		{
			ImGui::Begin("Setting");
			ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
			ImGui::End();
		}

		void OnEvent(Hickory::Event& event) override
		{
		}

		private:

			Hickory::ShaderLibrary m_ShaderLibrary;
			Hickory::Ref<Hickory::Shader> m_Shader;
			Hickory::Ref<Hickory::VertexArray> m_VertexArray;

			Hickory::Ref<Hickory::Shader> m_FlatColorShader;
			Hickory::Ref<Hickory::VertexArray> m_SquareVA;
			Hickory::Ref<Hickory::Texture2D> m_Texture;
			Hickory::Ref<Hickory::Texture2D> m_LogoTexture;

			Hickory::Camera m_Camera;
			glm::vec3 m_CameraPosition;

			float m_CameraMovementSpeed = 5.0f;
			float m_CameraRotation = 0.0f;
			float m_RotationSpeed = 90.0f;

			glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

};

class Sandbox : public Hickory::Application
{
	public:
		Sandbox()
		{
			PushLayer(new ExampleLayer());
			
		}

		~Sandbox()
		{

		}
};


Hickory::Application* Hickory::CreateApplication()
{
	return new Sandbox();
}