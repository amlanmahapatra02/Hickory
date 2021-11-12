#pragma once
#ifdef HK_PLATFORM_WINDOWS

extern Hickory::Application* Hickory::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Hickory::CreateApplication();
	app->Run();
	delete app;
}

#endif  
