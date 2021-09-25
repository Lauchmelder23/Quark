#pragma once

#include "Quark/Photon/Context.hpp"

struct GLFWwindow;

namespace Quark
{
	namespace Photon
	{
		class OpenGLContext : public Context
		{
		public:
			OpenGLContext(GLFWwindow* handle);

			void Init() override;
			void SwapBuffers() override;

		private:
			GLFWwindow* m_Handle;
		};
	}
}