#pragma once

#ifdef QK_PLATFORM_WINDOWS

#define QK_CREATE_APPLICATION Quark::CreateApplication
#define QK_CREATE_APP_SIGNATURE Quark::Application* QK_CREATE_APPLICATION
#define QK_SET_APPLICATION(x) QK_CREATE_APP_SIGNATURE() { return new x; }
	
extern QK_CREATE_APP_SIGNATURE();

int main(int argc, char** argv)
{
	Quark::Log::Init(); 
	QK_CORE_INFO("Initialized Logger");

	auto app = QK_CREATE_APPLICATION();
	app->Run();
	delete app;

	return 0;
}

#endif
