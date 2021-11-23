#include <Hickory.h>
#include "glm/glm.hpp"

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


		void OnEvent(Hickory::Event& event) override
		{
			HK_TRACE("{0}", event);
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