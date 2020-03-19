#include "Vantus.h"

class ExampleLeyer : public Vantus::Layer {
public:
	ExampleLeyer()
		: Layer("Example"){
	}

	void OnUpdate() override {
		VANTUS_INFO("ExampleLayer::Update");
	}

	void OnEvent(Vantus::Event& event) override {
		VANTUS_WARN("{0}", event);
	}
};

class Sandbox : public Vantus::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLeyer());
	}
	~Sandbox() {

	}
};

Vantus::Application* Vantus::CreateApplication() {
	return new Sandbox();
}