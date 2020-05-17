#include "vpch.h"

#include "Application.h"
#include "Vantus/Events/ApplicationEvent.h"
#include "Vantus/Renderer/Renderer.h"
#include "GLFW/glfw3.h"

namespace Vantus {

	Application* Application::m_Instance = nullptr;

	Vantus::Application::Application(){
		VANTUS_CORE_ASSERT(!m_Instance, "Application already exists!");
		m_Instance = this;

		m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallback(VANTUS_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Vantus::Application::~Application(){

	}

	void Application::Run(){		
		while (m_Running) {

			float time = (float)glfwGetTime();
			TimeStep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

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

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

}
