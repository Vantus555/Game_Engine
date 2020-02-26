#pragma once

#ifdef VANTUS_PLATFORM_WINDOWS

extern Vantus::Application* Vantus::CreateApplication();

void main(int argc, char** argv) {
	printf("Vantus Engine!\n");
	auto app = Vantus::CreateApplication();
	app->Run();
	delete app;
}

#endif;