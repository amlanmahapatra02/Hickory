#include "hkpch.h"

#include "Application.h"
#include "Hickory/Events/ApplicationEvent.h"

#include <glad/glad.h>

namespace Hickory
{
	#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)


	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));

		unsigned int id;
		glGenBuffers(1, &id);

	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& eve)
	{
		EventDispatcher dispatcher(eve);

		//check
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(Application::OnWindowClose));

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
			glClearColor(1, 0, 1, 1);
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