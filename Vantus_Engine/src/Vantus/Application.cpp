#include "vpch.h"

#include "Log.h"
#include "Application.h"
#include "Vantus/Events/ApplicationEvent.h"
#include "GLFW/glfw3.h"

namespace Vantus {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Vantus::Application::Application(){
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Vantus::Application::~Application(){

	}

	void Application::Run(){		
		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		VANTUS_CORE_INFO("{0}", e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

}
