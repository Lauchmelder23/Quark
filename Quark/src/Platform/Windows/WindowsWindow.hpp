#pragma once

#include "Quark/Window.hpp"

#include <GLFW/glfw3.h>

namespace Quark
{
	/**
	 * @brief A structure representing a desktop window on Windows
	 */
	class WindowsWindow : public Window
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
		};

		WindowData m_Data;
	};
}
