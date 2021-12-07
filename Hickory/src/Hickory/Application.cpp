#include "hkpch.h"

#include "Application.h"
#include "Hickory/Events/ApplicationEvent.h"
#include "imgui/imGuiLayer.h"
#include "Input.h"

#include <glad/glad.h>

namespace Hickory
{

	Application* Application::s_Instances = nullptr;

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

	Application::Application()
	{
		HK_CORE_ASSERT("Application already exists ", !s_Instances);
		s_Instances = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(HK_BIND_EVENT_FUNC(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);


		//indices
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,   0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f,	  0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,	0.5f, 0.0f,	  0.8f, 0.8f, 0.2f, 1.0f,
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));


		{
			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"}
			};

			m_VertexBuffer->SetLayout(layout);
		}

		uint32_t index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
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


		uint32_t indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
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

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& eve)
	{
		EventDispatcher dispatcher(eve);

		//check
		dispatcher.Dispatch<WindowCloseEvent>(HK_BIND_EVENT_FUNC(Application::OnWindowClose));

		//HK_CORE_TRACE("{0}", eve);

		//move backward on the m_layerStack to see if the event is handled
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(eve);

			if (eve.m_Handled)
			{
				break;
			}
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}
			
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& eve)
	{
		m_Running = false;
		return true;
	}
}