#include <Hickory.h>

class ExampleLayer : public Hickory::Layer
{
	public:
		ExampleLayer()
			:Layer("Example")
		{
		}

		void OnUpdate() override
		{
			HK_INFO("ExampleLayer :: Update");
		}

		void OnEvent(Hickory::Event& event) override
		{
			HK_TRACE("{0}", event);
		}
};

class Sandbox : public Hickory::Application
{
	public:
		Sandbox()
		{
			//PushLayer(new ExampleLayer());
			PushOverlay(new Hickory::ImGuiLayer());
		}

		~Sandbox()
		{

		}
};


Hickory::Application* Hickory::CreateApplication()
{
	return new Sandbox();
}