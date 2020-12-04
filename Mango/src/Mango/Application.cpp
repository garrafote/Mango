#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Mango {

	Mango::Application::Application()
	{
	}

	Mango::Application::~Application()
	{
	}
	
	void Application::Run()
	{
		WindowResizeEvent e(123, 456);
		MGO_TRACE(e);

		while (true)
		{

		}
	}
}

