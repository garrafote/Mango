#include <Mango.h>

class ExampleLayer : public Mango::Layer
{
public:
	ExampleLayer()
		: Layer("Example") { }

	void OnUpdate() override
	{
		if (Mango::Input::IsKeyPressed(MGO_KEY_TAB))
			MGO_TRACE("Tab key is pressed!");
	}

	void OnEvent(Mango::Event& event) override
	{
		MGO_TRACE("{0}", event);
	}

};

class Sandbox : public Mango::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Mango::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Mango::Application* Mango::CreateApplication()
{
	return new Sandbox();
}