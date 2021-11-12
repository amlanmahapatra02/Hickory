#pragma once
#ifdef HK_PLATFORM_WINDOWS

extern Hickory::Application* Hickory::CreateApplication();

int main(int argc, char** argv)
{
	Hickory::Log::Init();
	
	HK_CORE_INFO("Hello");
	
	int a = 5;
	HK_WARN("Hello {}", a);

	auto app = Hickory::CreateApplication();
	app->Run();
	delete app;
}

#endif  
