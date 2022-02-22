#include "qkpch.hpp"
#include "WindowsWindow.hpp"

#include "Quark/Events/ApplicationEvent.hpp"
#include "Quark/Events/MouseEvent.hpp"
#include "Quark/Events/KeyEvent.hpp"

#include "Platform/OpenGL/OpenGLContext.hpp"

QK_BEGIN

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int errcode, const char* desc)
	{
		QK_CORE_ERROR("GLFW Error ({0}): {1}", errcode, desc);
	}

	Window* Window::Create(const WindowProperties& props)
	{
		QK_CORE_ASSERT(
			props.Renderer == Photon::RendererAPI::API::OpenGL,
			"WindowsWindow can't be created with the requested RendererAPI (id={0})", static_cast<int>(props.Renderer)
		);

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
		m_Data.Context->SwapBuffers();
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

		QK_CORE_INFO("Creating window {0} ({1}, {2}). RendererAPI: {3}", props.Title, props.Width, props.Height, static_cast<int>(props.Renderer));

		if (!s_GLFWInitialized)
		{
			int result = glfwInit();
			QK_CORE_ASSERT(result, "Could not initialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);

		m_Data.Context = Photon::Context::Create(m_Window);

		try
		{
			m_Data.Context->Init();
		}
		catch (const std::runtime_error& exception)
		{
			QK_CORE_FATAL("Render context initialization error\n\t {0}", exception.what());
			throw exception;
		}

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(false);

		// Set GLFW callbacks
		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Context->FrameBufferResized();
		});

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

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int key)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(GetQuarkKeyCode(key));

			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyEvent* event = nullptr;
			switch (action)
			{
			case GLFW_PRESS:
				event = new KeyPressedEvent(GetQuarkKeyCode(key), 0);
				break;
			case GLFW_RELEASE:
				event = new KeyReleasedEvent(GetQuarkKeyCode(key));
				break;
			case GLFW_REPEAT:
				event = new KeyPressedEvent(GetQuarkKeyCode(key), 1);
				break;
			}

			QK_CORE_ASSERT(event != nullptr, "KeyEvent* was nullptr");
			data.EventCallback(*event);
			delete event;
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseButtonEvent* event = nullptr;
			switch (action)
			{
			case GLFW_PRESS:
				event = new MouseButtonPressedEvent(GetQuarkMouseButtonCode(button));
				break;
			case GLFW_RELEASE:
				event = new MouseButtonReleasedEvent(GetQuarkMouseButtonCode(button));
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
		delete m_Data.Context;
		glfwDestroyWindow(m_Window);
	}

QK_END
