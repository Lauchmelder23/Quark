#pragma once

#include <sstream>
#include "Event.hpp"

namespace Quark
{
	/**
	 * @brief Event for when the application window was resized
	 */
	class QUARK_API WindowResizeEvent : public Event
	{
	public:
		/**
		 * @brief        Create the event with the specified new window dimensions
		 * 
		 * @param width  New window width
		 * @param height New window height
		 */
		WindowResizeEvent(unsigned int width, unsigned int height) : 
			m_Width(width), m_Height(height) {}


		/**
		 * @brief   Retrieve new window width.
		 *
		 * @returns New window width
		 */
		inline unsigned int GetWidth() const { return m_Width; }

		/**
		 * @brief   Retrieve new window height.
		 * 
		 * @returns New window height
		 */
		inline unsigned int GetHeight() const { return m_Height; }

		/**
		 * @brief   Convenience function for printing event details
		 * 
		 * @returns Formatted string with event data
		 */
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


	/**
	 * @brief Event for when the application window was closed
	 */
	class QUARK_API WindowCloseEvent : public Event
	{
	public:
		/**
		 * @brief Create event
		 */
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/**
	 * @brief Event for when the application finished a tick
	 */
	class QUARK_API AppTickEvent : public Event
	{
	public:
		/**
		 * @brief Create event
		 */
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};


	/**
	 * @brief Event for when the application finished updating
	 */
	class QUARK_API AppUpdateEvent : public Event
	{
	public:
		/**
		 * @brief Create event
		 */
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/**
	 * @brief Event for when the application finished rendering
	 */
	class QUARK_API AppRenderEvent : public Event
	{
	public:
		/**
		 * @brief Create event
		 */
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}
