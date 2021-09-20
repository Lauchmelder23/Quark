#pragma once

#ifdef QK_PLATFORM_WINDOWS
	
extern Quark::Application* Quark::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Quark::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif
