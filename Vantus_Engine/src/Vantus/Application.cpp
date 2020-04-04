#include "vpch.h"

#include "Application.h"
#include "Vantus/Events/ApplicationEvent.h"
#include "glad/glad.h"

namespace Vantus {

	Application* Application::m_Instance = nullptr;

	static GLenum ShaderDataTypeToGLBaseType(ShaderDataType type) {
		switch (type) {
			case Vantus::ShaderDataType::None:		return GL_FLOAT;
			case Vantus::ShaderDataType::Float:		return GL_FLOAT;
			case Vantus::ShaderDataType::Float2:	return GL_FLOAT;
			case Vantus::ShaderDataType::Float3:	return GL_FLOAT;
			case Vantus::ShaderDataType::Float4:	return GL_FLOAT;
			case Vantus::ShaderDataType::Mat3:		return GL_FLOAT;
			case Vantus::ShaderDataType::Mat4:		return GL_FLOAT;
			case Vantus::ShaderDataType::Int:		return GL_INT;
			case Vantus::ShaderDataType::Int2:		return GL_INT;
			case Vantus::ShaderDataType::Int3:		return GL_INT;
			case Vantus::ShaderDataType::Int4:		return GL_INT;
			case Vantus::ShaderDataType::Bool:		return GL_BOOL;
		}

		VANTUS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Vantus::Application::Application() {
		VANTUS_CORE_ASSERT(!m_Instance, "Application already exists!");
		m_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(VANTUS_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);


		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[] = {
			-0.5,	-0.5,	0.0,	1.0,	0.0,	0.0,	0.0,
			0.0,	0.5,	0.0,	0.0,	0.0,	1.0,	0.0,
			0.5,	-0.5,	0.0,	1.0,	1.0,	0.0,	0.0
		};

		uint32_t indices[3] = { 0,1,2 };

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VertexBuffer->Bind();
		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color" }
			};

			m_VertexBuffer->SetLayout(layout);
		}
		uint32_t index = 0;
		for (auto& elem : m_VertexBuffer->GetLayout()) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 
				elem.GetComponentCount(), 
				ShaderDataTypeToGLBaseType(elem.Type), 
				elem.Normalized ? true : false, 
				m_VertexBuffer->GetLayout().GetStride(),
				(const void*)elem.Offset);
			index++;
		}

		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_IndexBuffer->Bind();


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
	}

	Vantus::Application::~Application(){

	}

	void Application::Run(){		
		while (m_Running) {
			glClearColor(0.1, 0.1, 0.1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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
