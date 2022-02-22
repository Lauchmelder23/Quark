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

class ExampleLayer : public Quark::Layer
{
public:
	ExampleLayer() : 
		Layer("Example") 
	{
		m_VertexArray.reset(Quark::Photon::VertexArray::Create());

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
		m_VertexBuffer.reset(Quark::Photon::VertexBuffer::Create(sizeof(vertices), vertices));

		Quark::Photon::BufferLayout layout = {
			{ Quark::Photon::ShaderDataType::Float3, "a_Position" },
			{ Quark::Photon::ShaderDataType::Float3, "a_Color" },
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[3 * 3] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
		m_IndexBuffer.reset(Quark::Photon::ElementBuffer::Create(9, indices));
		m_VertexArray->SetElementBuffer(m_IndexBuffer);

		std::string vertexShaderSrc = R"(
			#version 460 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec3 a_Color;

			layout(location = 0) out vec3 o_Color;

			void main()
			{
				o_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentShaderSrc = R"(
			#version 460 core

			layout(location = 0) in vec3 o_Color;
			layout(location = 0) out vec4 color;

			void main()
			{
				color = vec4(o_Color, 1.0);
			}
		)";

		try
		{
			m_Shader.reset(Quark::Photon::Shader::Create(vertexShaderSrc, fragmentShaderSrc));
		}
		catch (const std::runtime_error& exception)
		{
			QK_CORE_FATAL("Shader creation failed:\n\n{0}", exception.what());
			return;
		}
	}

	void OnUpdate() override 
	{
		Quark::Photon::RenderCommand::SetClearColor({ 0.2f, 0.1f, 0.4f, 1.0f });
		Quark::Photon::RenderCommand::Clear();

		Quark::Photon::Renderer::BeginScene();

		m_Shader->Bind();
		Quark::Photon::Renderer::Submit(m_VertexArray);

		Quark::Photon::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello, World!");
		ImGui::End();
	}

	void OnEvent(Quark::Event& event) override {}

private:
	std::shared_ptr<Quark::Photon::Shader> m_Shader;
	std::shared_ptr<Quark::Photon::VertexArray> m_VertexArray;
	std::shared_ptr<Quark::Photon::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Quark::Photon::ElementBuffer> m_IndexBuffer;
};

class Sandbox : public Quark::Application
{
public:
	Sandbox() :
		Quark::Application({ Quark::Photon::RendererAPI::API::OpenGL })
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {}
};

Quark::Application* Quark::CreateApplication()
{
	return new Sandbox();
}
