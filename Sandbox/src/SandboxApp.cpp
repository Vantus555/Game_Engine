#include "Vantus.h"

//#include "../imgui/imgui.h"

class ExampleLeyer : public Vantus::Layer {
public:
	ExampleLeyer()
		: Layer("Example"), 
		m_Camera(-1.6f * 2, 1.6f * 2, -0.9f * 2, 0.9f * 2), 
		m_CameraPosition({0.0})
	{
		m_VertexArray.reset(Vantus::VertexArray::Create());

		float vertices[] = {
			-0.5,	-0.5,	0.0,	1.0,	0.0,	0.0,	0.0,
			0.0,	0.5,	0.0,	0.0,	0.0,	1.0,	0.0,
			0.5,	-0.5,	0.0,	1.0,	1.0,	0.0,	0.0
		};

		std::shared_ptr<Vantus::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(Vantus::VertexBuffer::Create(vertices, sizeof(vertices)));

		Vantus::BufferLayout layout = {
			{ Vantus::ShaderDataType::Float3, "a_Position" },
			{ Vantus::ShaderDataType::Float4, "a_Color" }
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[] = { 0,1,2 };

		std::shared_ptr<Vantus::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(Vantus::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec4 v_Color;

			uniform mat4 u_ViewProjection;

			void main(){
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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
		m_Shader.reset(new Vantus::Shader(vertexSrc, fragmentSrc));

		/////////////////////////////////////////////////////////////////////
		//// Square
		/////////////////////////////////////////////////////////////////////

		m_SquareVA.reset(Vantus::VertexArray::Create());

		float squareVertices[] = {
			-0.75,	-0.75,	0.0,
			 0.75,	-0.75,	0.0,
			 0.75,	 0.75,	0.0,
			-0.75,	 0.75,	0.0
		};

		std::shared_ptr<Vantus::VertexBuffer> squareVB;
		squareVB.reset(Vantus::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ Vantus::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareVndices[] = { 0,1,2,2,3,0 };

		std::shared_ptr<Vantus::IndexBuffer> squareIB;
		squareIB.reset(Vantus::IndexBuffer::Create(squareVndices, sizeof(squareVndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string BlueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			void main(){
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
			
		)";

		std::string BlueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 u_Color;

			void main(){
				u_Color = vec4(0.2, 0.3, 0.8, 1.0);
			}
			
		)";
		m_BlueShader.reset(new Vantus::Shader(BlueShaderVertexSrc, BlueShaderFragmentSrc));
	}

	void OnUpdate(Vantus::TimeStep ts) override {
		VANTUS_INFO("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliSeconds());
		
		if (Vantus::Input::IsKeyPressed(VANTUS_KEY_LEFT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		else if(Vantus::Input::IsKeyPressed(VANTUS_KEY_RIGHT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;

		if (Vantus::Input::IsKeyPressed(VANTUS_KEY_UP))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		else if (Vantus::Input::IsKeyPressed(VANTUS_KEY_DOWN))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		if (Vantus::Input::IsKeyPressed(VANTUS_KEY_A))
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		else if (Vantus::Input::IsKeyPressed(VANTUS_KEY_D))
			m_CameraRotation += m_CameraRotationSpeed * ts;

		Vantus::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
		Vantus::RenderCommand::Clear();

		Vantus::Renderer::BeginScene(m_Camera);

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Vantus::Renderer::Submit(m_BlueShader, m_SquareVA);
		Vantus::Renderer::Submit(m_Shader, m_VertexArray);

		Vantus::Renderer::EndScene();
	}

	void OnEvent(Vantus::Event& event) override {}
private:
	std::shared_ptr<Vantus::Shader> m_Shader;
	std::shared_ptr<Vantus::VertexArray> m_VertexArray;

	std::shared_ptr<Vantus::Shader> m_BlueShader;
	std::shared_ptr<Vantus::VertexArray> m_SquareVA;

	Vantus::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 3.0;

	float m_CameraRotation = 0.0;
	float m_CameraRotationSpeed = 75;
};

class Sandbox : public Vantus::Application {
public:
	Sandbox() {
		this->GetWindow().SetVSync(true);
		PushLayer(new ExampleLeyer());
	}
	~Sandbox() {

	}
};

Vantus::Application* Vantus::CreateApplication() {
	return new Sandbox();
}