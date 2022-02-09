#include "hkpch.h"

#include "Application.h"
#include "Hickory/Events/ApplicationEvent.h"
#include "Hickory/imgui/imGuiLayer.h"
#include "Input.h"

#include <GLFW/glfw3.h>

#include "Hickory/Renderer/Renderer.h"

namespace Hickory
{
	Application* Application::s_Instances = nullptr;

	Application::Application()
		
	{
		HK_CORE_ASSERT("Application already exists ", !s_Instances);
		s_Instances = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(HK_BIND_EVENT_FUNC(Application::OnEvent));
		m_Window->SetVSync(false);

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

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

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		//check
		dispatcher.Dispatch<WindowCloseEvent>(HK_BIND_EVENT_FUNC(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(HK_BIND_EVENT_FUNC(Application::OnWindowResize));

		//HK_CORE_TRACE("{0}", eve);

		//move backward on the m_layerStack to see if the event is handled
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);

			if (e.m_Handled)
			{
				break;
			}
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime(); //Tempo
			Timestep DeltaTime = time - m_LastFrameTime;
			m_LastFrameTime = time;
			
			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(DeltaTime);
				}
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

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}