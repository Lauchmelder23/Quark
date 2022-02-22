#pragma once

#include "Quark/Window.hpp"
#include "Quark/Photon/Context.hpp"

#include <GLFW/glfw3.h>

QK_BEGIN

	/**
	 * @brief A structure representing a desktop window on Windows
	 */
	class WindowsWindow final : public Window
	{
	public:
		/**
		 * @brief       Create new Windows window with the given properties 
		 * 
		 * @param props Properties of the new window
		 */
		WindowsWindow(const WindowProperties& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		/**
		 * @brief   Retrieves the underlying window object, depending on the API used
		 *
		 * @returns An any containing a GLFWwindow*
		 */
		inline std::any GetNativeWindow() const override { return std::make_any<GLFWwindow*>(m_Window); }

		/**
		 * @brief	Retrieves the rendering API of the window
		 * 
		 * @returns An
		 */

	private:
		virtual void Init(const WindowProperties& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
			Photon::Context* Context;
		};

		WindowData m_Data;
	};

QK_END
