#include "hkpch.h"

#include "Application.h"
#include "Hickory/Events/ApplicationEvent.h"
#include "imgui/imGuiLayer.h"

#include <glad/glad.h>

namespace Hickory
{

	Application* Application::s_Instances = nullptr;

	Application::Application()
	{
		HK_CORE_ASSERT("Application already exists ", !s_Instances);
		s_Instances = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(HK_BIND_EVENT_FUNC(Application::OnEvent));

		unsigned int id;
		glGenBuffers(1, &id);

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

		HK_CORE_TRACE("{0}", eve);

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
			glClearColor(1, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			for (auto layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& eve)
	{
		m_Running = false;
		return m_Running;
	}
}