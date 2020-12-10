#pragma once

#include "Core.h"
#include "Window.h"

#include "Mango/LayerStack.h"
#include "Mango/Events/Event.h"
#include "Mango/Events/ApplicationEvent.h"

namespace Mango {

	class MANGO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

