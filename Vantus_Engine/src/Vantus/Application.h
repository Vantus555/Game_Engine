#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Vantus/Events/ApplicationEvent.h"
#include "Vantus/ImGui/ImGuiLayer.h"
#include "Vantus/Renderer/Shader.h"

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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* m_Instance;

		unsigned int m_VertexArray, m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;
	};
	
	// Определение для клиента
	Application* CreateApplication();
}

