#include "qkpch.hpp"
#include "OpenGLContext.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

QK_PHOTON_BEGIN

	OpenGLContext::OpenGLContext(GLFWwindow* handle) : m_Handle(handle) { }

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Handle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		QK_CORE_ASSERT(status, "Failed to initialize GLAD");
	}
		
	void OpenGLContext::SwapBuffers()
	{
		if (m_FrameBufferResized)
		{
			int width = 0, height = 0;
			glfwGetFramebufferSize(m_Handle, &width, &height);
			glViewport(0, 0, width, height);
		}

		glfwSwapBuffers(m_Handle);
	}

QK_PHOTON_END