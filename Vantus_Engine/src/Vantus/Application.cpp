#include "vpch.h"

#include "Application.h"
#include "Vantus/Events/ApplicationEvent.h"
#include "glad/glad.h"
#include "Vantus/Input.h"
namespace Vantus {

	Application* Application::m_Instance = nullptr;

	Vantus::Application::Application(){
		VANTUS_CORE_ASSERT(!m_Instance, "Application already exists!");
		m_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(VANTUS_BIND_EVENT_FN(Application::OnEvent));
	}

	Vantus::Application::~Application(){

	}

	void Application::Run(){		
		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			auto [x, y] = Input::GetMousePosition();
			VANTUS_CORE_WARN("{0}, {1}", x, y);

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(VANTUS_BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushLayer(overlay);
	}

	inline Application& Application::Get() {
		return *m_Instance;
	}

	inline Window& Application::GetWindow() {
		return *m_Window;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

}
