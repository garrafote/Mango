#pragma once
#include "Mango/Core/Base.h"

#include "Mango/Debug/Instrumentor.h"

#ifdef MANGO_PLATFORM_WINDOWS

extern Mango::Application* Mango::CreateApplication();

int main(int argc, char** argv)
{
	Mango::Log::Init();

	MGO_PROFILE_BEGIN_SESSION("Startup", "MangoProfile-Startup.json");
	Mango::Application* app = Mango::CreateApplication();
	MGO_PROFILE_END_SESSION();
	
	MGO_PROFILE_BEGIN_SESSION("Runtime", "MangoProfile-Runtime.json");
	app->Run();
	MGO_PROFILE_END_SESSION();

	MGO_PROFILE_BEGIN_SESSION("Shutdown", "MangoProfile-Shutdown.json");
	delete app;
	MGO_PROFILE_END_SESSION();
}

#endif