#pragma once

#include "Core.h"
#include "Window.h"
#include "Hickory/Events/Event.h"
#include "Hickory/Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Hickory/imgui/ImGuiLayer.h"


namespace Hickory
{
	class HICKORY_API Application
	{
		private:
			std::unique_ptr<Window> m_Window;
			ImGuiLayer* m_ImGuiLayer;

			bool OnWindowClose(WindowCloseEvent& eve);

			LayerStack m_LayerStack;
			bool m_Running = true;
			
			static Application* s_Instances;


		public:
			Application();
			virtual ~Application();

			void Run();

			void OnEvent(Event& eve);

			void PushLayer(Layer* layer);
			void PushOverlay(Layer* layer);

			inline Window& GetWindow() { return *m_Window; }
			inline static Application& Get() { return *s_Instances; }
	};

	Application* CreateApplication();
}

