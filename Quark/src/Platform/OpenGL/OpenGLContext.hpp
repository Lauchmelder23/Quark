#pragma once

#include "Quark/Photon/Context.hpp"

struct GLFWwindow;

QK_PHOTON_BEGIN

	/**
	* @brief Abstraction of an OpenGL rendering context
	*/
	class QUARK_API OpenGLContext : public Context
	{
	public:
		/**
		* @brief        Creates a new context but doesn't initialize it.
		* 
		* @param handle A pointer to the window API, in this case GLFW
		*/
		OpenGLContext(GLFWwindow* handle);

		/**
		* @brief Initialize a new OpenGL context and make it current. Set up GLAD.
		*/
		void Init() override;

		/**
		* @copydoc Context::SwapBuffers()
		*/
		void SwapBuffers() override;

	private:
		GLFWwindow* m_Handle;
	};

QK_PHOTON_END
