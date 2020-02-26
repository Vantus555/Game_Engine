#include "Vantus.h"

class Sandbox : public Vantus::Application {

public:
	Sandbox() {

	}
	~Sandbox() {

	}
};

Vantus::Application* Vantus::CreateApplication() {
	return new Sandbox();
}