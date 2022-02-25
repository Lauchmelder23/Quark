#include <Quark.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"

#include <Platform/OpenGL/OpenGLShader.hpp>

class ExampleLayer : public Qk::Layer
{
public:
	ExampleLayer() : 
		Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_SquarePosition(0.0f)
	{
		m_SquareVertexArray = Qk::Photon::VertexArray::Create();

		float squareVertices[4 * (3 + 2)] = {
			-1.1f, -1.1f, 0.0f,		0.0f, 0.0f,
			-1.1f,  1.1f, 0.0f,		0.0f, 1.0f,
			 1.1f,  1.1f, 0.0f,		1.0f, 1.0f,
			 1.1f, -1.1f, 0.0f,		1.0f, 0.0f
		};
		Qk::Reference<Qk::Photon::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer = Qk::Photon::VertexBuffer::Create(sizeof(squareVertices), squareVertices);

		Qk::Photon::BufferLayout squareLayout = {
			{ Qk::Photon::ShaderDataType::Float3, "a_Position" },
			{ Qk::Photon::ShaderDataType::Float2, "a_TexCoord" }
		};
		squareVertexBuffer->SetLayout(squareLayout);
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		unsigned int squareIndices[6] = {
			0, 1, 2,
			0, 2, 3
		};
		Qk::Reference<Qk::Photon::ElementBuffer> squareIndexBuffer;
		squareIndexBuffer = Qk::Photon::ElementBuffer::Create(sizeof(squareIndices), squareIndices);

		m_SquareVertexArray->SetElementBuffer(squareIndexBuffer);

		std::string squareVertexShaderSrc = R"(
			#version 460 core 

			layout (location = 0) in vec3 a_Position;			

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Model;

			void main()
			{
				gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0f);
			}	
		)";

		std::string squareFragmentShaderSrc = R"(
			#version 460 core

			out vec4 color;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";
		
		try
		{
			m_FlatColorShader = Qk::Photon::Shader::Create(squareVertexShaderSrc, squareFragmentShaderSrc);
		}
		catch (const std::runtime_error& err)
		{
			QK_CORE_FATAL("FlatColorShader creation failed:\n\n{0}", err.what());
			return;
		}

		std::string textureVertexShaderSrc = R"(
			#version 460 core 
		
			layout (location = 0) in vec3 a_Position;			
			layout (location = 1) in vec2 a_TexCoord;		

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Model;
		
			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0f);
			}	
		)";
		
		std::string textureFragmentShaderSrc = R"(
			#version 460 core
		
			in vec2 v_TexCoord;

			out vec4 color;
			
			uniform sampler2D u_Texture;
		
			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		try
		{
			m_TextureShader = Qk::Photon::Shader::Create(textureVertexShaderSrc, textureFragmentShaderSrc);
		}
		catch (const std::runtime_error& err)
		{
			QK_CORE_FATAL("TextureShader creation failed:\n\n{0}", err.what());
			return;
		}

		m_PoggersTexture = Qk::Photon::Texture2D::Create("assets/textures/poggers.png");
		m_TextureShader->Bind();
		std::dynamic_pointer_cast<Qk::Photon::OpenGLShader>(m_TextureShader)->SetUniformInt("u_Texture", 0);
	}

	void OnUpdate(Qk::Timestep dt) override 
	{
		glm::vec3 moveDirection(0.0f);
		float moveSpeed = 2.0f * dt;

		if (Qk::Input::IsKeyPressed(Qk::Key::W))
			moveDirection += glm::vec3(0.0f, 1.0f, 0.0f);

		if (Qk::Input::IsKeyPressed(Qk::Key::A))
			moveDirection += glm::vec3(-1.0f, 0.0f, 0.0f);

		if (Qk::Input::IsKeyPressed(Qk::Key::S))
			moveDirection += glm::vec3(0.0f, -1.0f, 0.0f);

		if (Qk::Input::IsKeyPressed(Qk::Key::D))
			moveDirection += glm::vec3(1.0f, 0.0f, 0.0f);

		if (Qk::Input::IsKeyPressed(Qk::Key::Q))
			m_Camera.SetRotation(m_Camera.GetRotation() + 90.0f * dt);

		if (Qk::Input::IsKeyPressed(Qk::Key::E))
			m_Camera.SetRotation(m_Camera.GetRotation() - 90.0f * dt);

		if (glm::length(moveDirection) > 0.01f)
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::normalize(moveDirection) * moveSpeed);

		Qk::Photon::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Qk::Photon::RenderCommand::Clear();

		Qk::Photon::Renderer::BeginScene(m_Camera);

		m_FlatColorShader->Bind();

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 2.4f, y * 2.4f, 0.0f);
				glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f));
				transform = glm::translate(transform, pos);

				if ((x + y) % 2 == 0)
					std::dynamic_pointer_cast<Qk::Photon::OpenGLShader>(m_FlatColorShader)->SetUniformFloat3("u_Color", redColor);
				else
					std::dynamic_pointer_cast<Qk::Photon::OpenGLShader>(m_FlatColorShader)->SetUniformFloat3("u_Color", blueColor);

				Qk::Photon::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, transform);
			}
		}
		
		m_PoggersTexture->Bind(0);

		Qk::Photon::Renderer::Submit(m_TextureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(0.7f)));

		Qk::Photon::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Example Settings");

		if (ImGui::CollapsingHeader("Grid colors"))
		{
			ImGui::ColorEdit3("Color 1", glm::value_ptr(redColor));
			ImGui::ColorEdit3("Color 2", glm::value_ptr(blueColor));
		}

		ImGui::End();
	}

	void OnEvent(Qk::Event& event) override 
	{
		
	}

private:
	Qk::Reference<Qk::Photon::Shader> m_FlatColorShader;
	Qk::Reference<Qk::Photon::Shader> m_TextureShader;

	Qk::Reference<Qk::Photon::Texture2D> m_PoggersTexture;

	Qk::Reference<Qk::Photon::VertexArray> m_SquareVertexArray;

	Qk::Photon::OrthographicCamera m_Camera;

	glm::vec3 m_SquarePosition;
	glm::vec3 redColor = glm::vec3(1.0f, 0.35f, 0.35f);
	glm::vec3 blueColor = glm::vec3(0.35f, 0.35f, 1.0f);
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

QK_SET_APPLICATION(Sandbox);
