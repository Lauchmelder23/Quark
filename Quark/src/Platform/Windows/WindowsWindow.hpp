#pragma once

#include "Quark/Window.hpp"
#include "Quark/Photon/Context.hpp"

#include <GLFW/glfw3.h>

namespace Quark
{
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

		virtual inline unsigned int GetWidth() const override { return m_Data.Width; }
		virtual inline unsigned int GetHeight() const override { return m_Data.Height; }

		virtual inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		/**
		 * @brief   Retrieves the underlying window object, depending on the API used
		 *
		 * @returns An any containing a GLFWwindow*
		 */
		virtual inline std::any GetNativeWindow() const override { return std::make_any<GLFWwindow*>(m_Window); }

	private:
		virtual void Init(const WindowProperties& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		Photon::Context* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}
