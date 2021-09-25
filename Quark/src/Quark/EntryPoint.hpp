#pragma once

#ifdef QK_PLATFORM_WINDOWS
	
extern Quark::Application* Quark::CreateApplication();

int main(int argc, char** argv)
{
	Quark::Log::Init(); 
	QK_CORE_INFO("Initialized Logger");

	auto app = Quark::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif
