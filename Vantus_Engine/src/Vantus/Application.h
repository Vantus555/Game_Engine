#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Vantus {
	class VANTUS_API Application
	{

	public:
		Application();
		virtual ~Application();

		void Run();
	};
	
	// Определение для клиента
	Application* CreateApplication();
}

