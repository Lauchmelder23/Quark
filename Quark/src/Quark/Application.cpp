#include "qkpch.hpp"
#include "Application.hpp"

#include "Events/ApplicationEvent.hpp"
#include "Log.hpp"

namespace Quark
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}