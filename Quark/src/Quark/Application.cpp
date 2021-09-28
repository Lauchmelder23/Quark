#include "qkpch.hpp"
#include "Application.hpp"

#include "Input.hpp"

#include <glad/glad.h>

namespace Quark
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const Photon::VertexShaderBinary& vertexShaderSrc, const Photon::FragmentShaderBinary& fragmentShaderSrc, const std::vector<Photon::RendererAPI> desiredRenderAPIs)
	{
		s_Instance = this;
		m_Window = nullptr;
		
		for (Photon::RendererAPI api : desiredRenderAPIs)
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
		
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 3 * 3] = {
			-0.5f, 0.0f, 0.0f,
			0.0f, 0.866f, 0.0f,
			0.5f, 0.0f, 0.0f,

			-1.0f, -0.886f, 0.0f,
			-0.5f, 0.0f, 0.0f,
			0.0f, -0.886f, 0.0f,

			-0.0f, -0.886f, 0.0f,
			0.5f, 0.0f, 0.0f,
			1.0f, -0.886f, 0.0f
		};
		m_VertexBuffer.reset(Photon::VertexBuffer::Create(sizeof(vertices), vertices));

		Photon::BufferLayout layout = {
			{ Photon::ShaderDataType::Float3, "a_Position" },
			{ Photon::ShaderDataType::Float4, "a_Color" },
			{ Photon::ShaderDataType::Float3, "a_Normal" }
		};

		m_VertexBuffer->SetLayout(layout);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		unsigned int indices[3 * 3] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
		m_IndexBuffer.reset(Photon::IndexBuffer::Create(9, indices));

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
			glClearColor(0.2f, 0.1f, 0.4f, 1.0f);
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
}