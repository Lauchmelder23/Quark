#include "qkpch.hpp"
#include "OpenGLContext.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Quark
{
	namespace Photon
	{
		OpenGLContext::OpenGLContext(GLFWwindow* handle) :
			m_Handle(handle)
		{

		}

		void OpenGLContext::Init()
		{
			glfwMakeContextCurrent(m_Handle);
			int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			QK_CORE_ASSERT(status, "Failed to initialize GLAD");
		}
		
		void OpenGLContext::SwapBuffers()
		{
			glfwSwapBuffers(m_Handle);
		}
	}
}