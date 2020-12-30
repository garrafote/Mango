#pragma once


#ifdef MANGO_PLATFORM_WINDOWS

extern Mango::Application* Mango::CreateApplication();

int main(int argc, char** argv)
{
	Mango::Log::Init();
	MGO_CORE_TRACE("Initialized Core Logger");
	MGO_INFO("Welcome to Mango, {0}!", 42);

	Mango::Application* app = Mango::CreateApplication();
	app->Run();
	delete app;
}

#endif