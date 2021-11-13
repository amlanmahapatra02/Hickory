#include "Application.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Hickory
{
	Hickory::Application::Application()
	{

	}

	Hickory::Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent windowevent(1280, 720);

		if (windowevent.IsInCategory(EventCategoryApplication))
		{
			HK_TRACE(windowevent);
		}

		if (windowevent.IsInCategory(EventCategoryInput))
		{
			HK_TRACE(windowevent);
		}
		
		while (true);
	}

}