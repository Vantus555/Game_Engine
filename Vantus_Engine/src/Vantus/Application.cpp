#include "vpch.h"

#include "Application.h"
#include "Vantus/Events/ApplicationEvent.h"
#include "Vantus/Renderer/Renderer.h"

namespace Vantus {

	Application* Application::m_Instance = nullptr;

	Vantus::Application::Application() {
		VANTUS_CORE_ASSERT(!m_Instance, "Application already exists!");
		m_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(VANTUS_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());

		float vertices[] = {
			-0.5,	-0.5,	0.0,	1.0,	0.0,	0.0,	0.0,
			0.0,	0.5,	0.0,	0.0,	0.0,	1.0,	0.0,
			0.5,	-0.5,	0.0,	1.0,	1.0,	0.0,	0.0
		};

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[] = { 0,1,2 };

		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec4 v_Color;

			void main(){
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
			
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 u_Color;
			in vec4 v_Color;

			void main(){
				u_Color = v_Color;
			}
			
		)";
		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

		/////////////////////////////////////////////////////////////////////
		//// Square
		/////////////////////////////////////////////////////////////////////

		m_SquareVA.reset(VertexArray::Create()); 

		float squareVertices[] = {
			-0.75,	-0.75,	0.0,
			 0.75,	-0.75,	0.0,
			 0.75,	 0.75,	0.0,
			-0.75,	 0.75,	0.0
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareVndices[] = { 0,1,2,2,3,0 };

		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareVndices, sizeof(squareVndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string BlueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			void main(){
				gl_Position = vec4(a_Position, 1.0);
			}
			
		)";

		std::string BlueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 u_Color;

			void main(){
				u_Color = vec4(0.2, 0.3, 0.8, 1.0);
			}
			
		)";
		m_BlueShader.reset(new Shader(BlueShaderVertexSrc, BlueShaderFragmentSrc));
	}

	Vantus::Application::~Application(){

	}

	void Application::Run(){		
		while (m_Running) {
			RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_BlueShader->Bind();
			Renderer::Submit(m_SquareVA);

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

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
