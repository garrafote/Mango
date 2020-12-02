#pragma once


#ifdef MANGO_PLATFORM_WINDOWS

extern Mango::Application* Mango::CreateApplication();

int main(int argc, char** argv)
{
	Mango::Application* app = Mango::CreateApplication();
	app->Run();
	delete app;
}

#endif