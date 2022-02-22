#include <Quark.hpp>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui.h"

glm::mat4 camera(float Translate, const glm::vec2& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));

	return Projection * View * Model;
}

class ExampleLayer : public Qk::Layer
{
public:
	ExampleLayer() : 
		Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
#pragma region Triangles
		m_VertexArray.reset(Qk::Photon::VertexArray::Create());

		float vertices[3 * 3 * (3 * 3)] = {
			-0.5f, 0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
			0.0f, 0.866f, 0.0f,		0.0f, 1.0f, 0.0f,
			0.5f, 0.0f, 0.0f,		0.0f, 0.0f, 1.0f,

			-1.0f, -0.886f, 0.0f,	0.0f, 0.0f, 1.0f,
			-0.5f, 0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
			0.0f, -0.886f, 0.0f,	0.0f, 1.0f, 0.0f,

			-0.0f, -0.886f, 0.0f,	0.0f, 1.0f, 0.0f,
			0.5f, 0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
			1.0f, -0.886f, 0.0f,	1.0f, 0.0f, 0.0f
		};
		std::shared_ptr<Qk::Photon::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Qk::Photon::VertexBuffer::Create(sizeof(vertices), vertices));

		Qk::Photon::BufferLayout layout = {
			{ Qk::Photon::ShaderDataType::Float3, "a_Position" },
			{ Qk::Photon::ShaderDataType::Float3, "a_Color" },
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3 * 3] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
		std::shared_ptr<Qk::Photon::ElementBuffer> indexBuffer;
		indexBuffer.reset(Qk::Photon::ElementBuffer::Create(9, indices));
		m_VertexArray->SetElementBuffer(indexBuffer);

		std::string vertexShaderSrc = R"(
			#version 460 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec3 a_Color;

			out vec3 o_Color;

			uniform mat4 u_ViewProjection;

			void main()
			{
				o_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentShaderSrc = R"(
			#version 460 core

			in vec3 o_Color;
			out vec4 color;

			void main()
			{
				color = vec4(o_Color, 1.0);
			}
		)";

		try
		{
			m_Shader.reset(Qk::Photon::Shader::Create(vertexShaderSrc, fragmentShaderSrc));
		}
		catch (const std::runtime_error& exception)
		{
			QK_CORE_FATAL("Shader creation failed:\n\n{0}", exception.what());
			return;
		}

#pragma endregion

#pragma region Square

		m_SquareVertexArray.reset(Qk::Photon::VertexArray::Create());

		float squareVertices[4 * 3] = {
			-1.1f, -1.1f, 0.0f,
			-1.1f,  1.1f, 0.0f,
			 1.1f,  1.1f, 0.0f,
			 1.1f, -1.1f, 0.0f
		};
		std::shared_ptr<Qk::Photon::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Qk::Photon::VertexBuffer::Create(sizeof(squareVertices), squareVertices));

		Qk::Photon::BufferLayout squareLayout = {
			{ Qk::Photon::ShaderDataType::Float3, "a_Position" }
		};
		squareVertexBuffer->SetLayout(squareLayout);
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		unsigned int squareIndices[6] = {
			0, 1, 2,
			0, 2, 3
		};
		std::shared_ptr<Qk::Photon::ElementBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Qk::Photon::ElementBuffer::Create(sizeof(squareIndices), squareIndices));

		m_SquareVertexArray->SetElementBuffer(squareIndexBuffer);

		std::string squareVertexShaderSrc = R"(
			#version 460 core 

			layout (location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
			}	
		)";

		std::string squareFragmentShaderSrc = R"(
			#version 460 core

			out vec4 color;
			
			void main()
			{
				color = vec4(0.6f, 0.6f, 1.0f, 1.0f);
			}
		)";
		m_SquareShader.reset(Qk::Photon::Shader::Create(squareVertexShaderSrc, squareFragmentShaderSrc));

#pragma endregion
	}

	void OnUpdate() override 
	{
		glm::vec3 moveDirection(0.0f);
		float moveSpeed = 0.005f;

		if (Qk::Input::IsKeyPressed(Qk::Key::W))
			moveDirection += glm::vec3(0.0f, 1.0f, 0.0f);

		if (Qk::Input::IsKeyPressed(Qk::Key::A))
			moveDirection += glm::vec3(-1.0f, 0.0f, 0.0f);

		if (Qk::Input::IsKeyPressed(Qk::Key::S))
			moveDirection += glm::vec3(0.0f, -1.0f, 0.0f);

		if (Qk::Input::IsKeyPressed(Qk::Key::D))
			moveDirection += glm::vec3(1.0f, 0.0f, 0.0f);

		if (glm::length(moveDirection) > 0.01f)
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::normalize(moveDirection) * moveSpeed);

		Qk::Photon::RenderCommand::SetClearColor({ 0.2f, 0.1f, 0.4f, 1.0f });
		Qk::Photon::RenderCommand::Clear();

		Qk::Photon::Renderer::BeginScene(m_Camera);

		Qk::Photon::Renderer::Submit(m_SquareShader, m_SquareVertexArray);
		Qk::Photon::Renderer::Submit(m_Shader, m_VertexArray);

		Qk::Photon::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello, World!");
		ImGui::End();
	}

	void OnEvent(Qk::Event& event) override 
	{
		
	}

private:
	std::shared_ptr<Qk::Photon::Shader> m_Shader;
	std::shared_ptr<Qk::Photon::Shader> m_SquareShader;

	std::shared_ptr<Qk::Photon::VertexArray> m_VertexArray;
	std::shared_ptr<Qk::Photon::VertexArray> m_SquareVertexArray;

	Qk::Photon::OrthographicCamera m_Camera;
};

class Sandbox : public Qk::Application
{
public:
	Sandbox() :
		Qk::Application({ Qk::Photon::RendererAPI::API::OpenGL })
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {}
};

Qk::Application* Qk::CreateApplication()
{
	return new Sandbox();
}
