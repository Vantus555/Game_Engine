#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Log.h"

namespace Vantus {

	Vantus::Application::Application(){

	}

	Vantus::Application::~Application(){

	}

	void Application::Run(){
		Vantus::Log::Init();
		KeyPressedEvent e(10, 10);
		
		if (e.IsInCategory(EventCategoryKeyboard)) {
			VANTUS_WARN(e.ToString());
		}
		while (true);
	}

}
