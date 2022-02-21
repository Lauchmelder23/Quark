#include "qkpch.hpp"
#include "Application.hpp"

#include "Input.hpp"

#include <glad/glad.h>

namespace Quark
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const std::vector<Photon::RendererAPI::API> desiredRenderAPIs)
	{
		s_Instance = this;
		m_Window = nullptr;
		
		for (Photon::RendererAPI::API api : desiredRenderAPIs)
		{
			try
			{
				m_Window = std::unique_ptr<Window>(Window::Create(WindowProperties("Quark Engine", 1280, 720, api)));
				break;
			}
			catch (const std::runtime_error& exception)
			{
				QK_CORE_ERROR("Window creation failed with requested API (id={0}):\n\t{1}", static_cast<int>(api), exception.what());
				m_Window = nullptr;
			}
		}

		if (m_Window == nullptr)
		{
			QK_CORE_FATAL("Window creation completely failed. Exiting.");
			m_Running = false;
			return;
		}

		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(Photon::VertexArray::Create());

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
		m_VertexBuffer.reset(Photon::VertexBuffer::Create(sizeof(vertices), vertices));

		Photon::BufferLayout layout = {
			{ Photon::ShaderDataType::Float3, "a_Position" },
			{ Photon::ShaderDataType::Float3, "a_Color" },
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[3 * 3] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
		m_IndexBuffer.reset(Photon::ElementBuffer::Create(9, indices));
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
			m_Shader.reset(Photon::Shader::Create(vertexShaderSrc, fragmentShaderSrc));
		}
		catch (const std::runtime_error& exception)
		{
			QK_CORE_FATAL("Shader creation failed:\n\n{0}", exception.what());
			m_Running = false;
			return;
		}
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		for (std::vector<Layer*>::reverse_iterator it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); it++)
		{
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			Photon::RenderCommand::SetClearColor({ 0.2f, 0.1f, 0.4f, 1.0f });
			Photon::RenderCommand::Clear();

			Photon::Renderer::BeginScene();
	
			m_Shader->Bind();
			Photon::Renderer::Submit(m_VertexArray);

			Photon::Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}
}