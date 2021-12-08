#pragma once

#include "Core.h"
#include "Window.h"
#include "Hickory/Events/Event.h"
#include "Hickory/Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Hickory/imgui/ImGuiLayer.h"

#include "Hickory/Renderer/Shader.h"
#include "Hickory/Renderer/Buffer.h"
#include "Hickory/Renderer/VertexArray.h"


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

			std::shared_ptr<Shader> m_Shader;
			std::shared_ptr<VertexArray> m_VertexArray;
			std::shared_ptr<VertexBuffer> m_VertexBuffer;
			std::shared_ptr<IndexBuffer> m_IndexBuffer;

			std::shared_ptr<Shader> m_BlueShader;
			std::shared_ptr<VertexArray> m_SquareVA;


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

