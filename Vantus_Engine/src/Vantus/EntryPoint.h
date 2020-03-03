#pragma once

#ifdef VANTUS_PLATFORM_WINDOWS

extern Vantus::Application* Vantus::CreateApplication();

void main(int argc, char** argv) {
	Vantus::Log::Init();
	VANTUS_CORE_WARN("Init Log");
	int a = 555;
	VANTUS_INFO("Hello world! Some number = {0}",a);

	auto app = Vantus::CreateApplication();
	app->Run();
	delete app;
}

#endif;