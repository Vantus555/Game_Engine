#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Vantus/Events/ApplicationEvent.h"
#include "Vantus/ImGui/ImGuiLayer.h"
#include "Vantus/Core/TimeStep.h"

namespace Vantus {
	class VANTUS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() {
			return *m_Instance;
		}
		inline Window& GetWindow() {
			return *m_Window;
		}
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0;

		static Application* m_Instance;
	};
	
	// ����������� ��� �������
	Application* CreateApplication();
}

