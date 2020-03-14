#include "vpch.h"
#include "Application.h"

#include "Vantus/Events/ApplicationEvent.h"
//#include "Vantus/Log.h"

#include <GLFW/glfw3.h>

namespace Vantus {

	Vantus::Application::Application(){
		m_Window = std::unique_ptr<Window>(Window::Create());
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

}
