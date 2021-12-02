#include <Hickory.h>

#include "imgui/imgui.h"

class ExampleLayer : public Hickory::Layer
{
	public:
		ExampleLayer()
			:Layer("Example")
		{
		}

		void OnUpdate() override
		{
			
		}

		virtual void OnImGuiRender() override
		{
			ImGui::Begin("Test");
			ImGui::Text("Hello World");
			ImGui::End();
		}

		void OnEvent(Hickory::Event& event) override
		{
			if (event.GetEventType() == Hickory::EventType::KeyPressed)
			{
				Hickory::KeyPressedEvent& e = (Hickory::KeyPressedEvent&)event;
				if (e.GetKeyCode() == HK_KEY_TAB)
				{
					HK_TRACE("Tab Key was Pressed! ");
				}
			}
		}
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