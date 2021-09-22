#include "qkpch.hpp"
#include "WindowsWindow.hpp"

#include "Quark/Events/ApplicationEvent.hpp"
#include "Quark/Events/MouseEvent.hpp"
#include "Quark/Events/KeyEvent.hpp"

namespace Quark
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int errcode, const char* desc)
	{
		QK_CORE_ERROR("GLFW Error ({0}): {1}", errcode, desc);
	}

	Window* Window::Create(const WindowProperties& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::Init(const WindowProperties& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		QK_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			int result = glfwInit();
			QK_CORE_ASSERT(result, "Could not initialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyEvent* event = nullptr;
			switch (action)
			{
			case GLFW_PRESS:
				event = new KeyPressedEvent(key, 0);
				break;
			case GLFW_RELEASE:
				event = new KeyReleasedEvent(key);
				break;
			case GLFW_REPEAT:
				event = new KeyPressedEvent(key, 1);
				break;
			}

			QK_CORE_ASSERT(event != nullptr, "KeyEvent* was nullptr");
			data.EventCallback(*event);
			delete event;
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int key, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseButtonEvent* event = nullptr;
			switch (action)
			{
			case GLFW_PRESS:
				event = new MouseButtonPressedEvent(key);
				break;
			case GLFW_RELEASE:
				event = new MouseButtonReleasedEvent(key);
				break;
			}

			QK_CORE_ASSERT(event != nullptr, "MouseButtonEvent* was nullptr");
			data.EventCallback(*event);
			delete event;
		});
		
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

}