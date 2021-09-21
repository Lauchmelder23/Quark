#pragma once

#include <sstream>
#include "Event.hpp"

namespace Quark
{
	/// <summary>
	/// Event for when the application window was resized
	/// </summary>
	class QUARK_API WindowResizeEvent : public Event
	{
	public:
		/// <summary>
		/// Create the event with the specified new window dimensions
		/// </summary>
		/// <param name="width">New window width</param>
		/// <param name="height">new window height</param>
		WindowResizeEvent(unsigned int width, unsigned int height) : 
			m_Width(width), m_Height(height) {}


		/// <summary>
		/// Retrieve new window width
		/// </summary>
		/// <returns>New window width</returns>
		inline unsigned int GetWidth() const { return m_Width; }

		/// <summary>
		/// Retrieve new window height
		/// </summary>
		/// <returns>New window height</returns>
		inline unsigned int GetHeight() const { return m_Height; }

		/// <summary>
		/// Convenience function for printing event details
		/// </summary>
		/// <returns>Formatted string with event data</returns>
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_Width, m_Height;
	};

	/// <summary>
	/// Event for when the application window was closed
	/// </summary>
	class QUARK_API WindowCloseEvent : public Event
	{
	public:
		/// <summary>
		/// Create event
		/// </summary>
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/// <summary>
	/// Event for when the application finished a tick
	/// </summary>
	class QUARK_API AppTickEvent : public Event
	{
	public:
		/// <summary>
		/// Create event
		/// </summary>
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/// <summary>
	/// Event for when the application finished updating
	/// </summary>
	class QUARK_API AppUpdateEvent : public Event
	{
	public:
		/// <summary>
		/// Create event
		/// </summary>
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/// <summary>
	/// Event for when the application finished rendering
	/// </summary>
	class QUARK_API AppRenderEvent : public Event
	{
	public:
		/// <summary>
		/// Create evnet
		/// </summary>
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}
