#pragma once

#include "Core.h"
#include "Window.h"
#include "Hickory/Events/Event.h"
#include "Hickory/Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Hickory/imgui/ImGuiLayer.h"

#include "Hickory/Renderer/Shader.h"
#include "Hickory/Renderer/Buffer.h"


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

			unsigned int m_VertexArray;
			std::unique_ptr<Shader> m_Shader;
			std::unique_ptr<VertexBuffer> m_VertexBuffer;
			std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};

	Application* CreateApplication();
}

