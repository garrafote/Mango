#pragma once

#include "Mango/Core/Base.h"

#include "Mango/Core/Window.h"
#include "Mango/Core/LayerStack.h"
#include "Mango/Events/Event.h"
#include "Mango/Events/ApplicationEvent.h"

#include "Mango/Core/Timestep.h"

#include "Mango/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Mango {

	class Application
	{
	public:
		Application(const std::string& name = "Mango Application");
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		void Run();
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

