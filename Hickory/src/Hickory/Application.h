#pragma once
#include "Core.h"


namespace Hickory
{
	class HICKORY_API Application
	{
		public:
			Application();
			virtual ~Application();
			void Run();
	};

	//To be defined in Sandbox
	Application* CreateApplication();
}


