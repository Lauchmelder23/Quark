#pragma once

#include "qkpch.hpp"

#include "Quark/Core.hpp"
#include "Quark/Events/Event.hpp"

namespace Quark
{
	/// <summary>
	/// A structure that contains basic information and properties about the window
	/// </summary>
	struct WindowProperties
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(const std::string& title = "Quark Engine", unsigned int width = 1280, unsigned int height = 720) :
			Title(title), Width(width), Height(height)
		{
		}
	};

	/// <summary>
	/// Abstract class representing a desktop window
	/// </summary>
	class QUARK_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		/// <summary>
		/// Callback that gets called if the window should update. It is called once every frame
		/// </summary>
		virtual void OnUpdate() = 0;

		/// <summary>
		/// Get width of the window
		/// </summary>
		/// <returns>The width of the window</returns>
		virtual unsigned int GetWidth() const = 0;

		/// <summary>
		/// Get height of the window
		/// </summary>
		/// <returns>The height of the window</returns>
		virtual unsigned int GetHeight() const = 0;


		/// <summary>
		/// Sets the function that should be called if an event occurs
		/// </summary>
		/// <param name="callback">The function to call</param>
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		/// <summary>
		/// Enables/Disables VSync for this window
		/// </summary>
		/// <param name="enabled">Whether to enable VSync</param>
		virtual void SetVSync(bool enabled) = 0;

		/// <summary>
		/// Checks whether VSync is enabled for this window
		/// </summary>
		/// <returns><c>True</c> if VSync is enabled</returns>
		virtual bool IsVSync() const = 0;


		/// <summary>
		/// Creates a new window
		/// </summary>
		/// <param name="props">The properties of the window</param>
		/// <returns>A pointer to the newly created window</returns>
		static Window* Create(const WindowProperties& props = WindowProperties());
	};
}
