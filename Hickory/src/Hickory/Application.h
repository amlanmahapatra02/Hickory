#pragma once

#include "Core.h"
#include "Window.h"
#include "Hickory/Events/Event.h"
#include "Hickory/Events/ApplicationEvent.h"
#include "LayerStack.h"


namespace Hickory
{
	class HICKORY_API Application
	{
		private:
			std::unique_ptr<Window> m_Window;
			bool m_Running = true;
			bool OnWindowClose(WindowCloseEvent& eve);
			LayerStack m_LayerStack;

		public:
			Application();
			virtual ~Application();

			void Run();

			void OnEvent(Event& eve);

			void PushLayer(Layer* layer);
			void PushOverlay(Layer* layer);
	};

	Application* CreateApplication();
}

