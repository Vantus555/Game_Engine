#pragma once

#include "Core.h"

namespace Vantus {
	class VANTUS_API Application
	{

	public:
		Application();
		virtual ~Application();

		void Run();
	};
	
	// ����������� ��� �������
	Application* CreateApplication();
}

