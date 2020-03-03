#pragma once

#ifdef VANTUS_PLATFORM_WINDOWS

extern Vantus::Application* Vantus::CreateApplication();

void main(int argc, char** argv) {
	Vantus::Log::Init();
	Vantus::Log::GetCoreLogger()->warn("Init Log");
	Vantus::Log::GetClientLogger()->info("Hello world!");

	auto app = Vantus::CreateApplication();
	app->Run();
	delete app;
}

#endif;