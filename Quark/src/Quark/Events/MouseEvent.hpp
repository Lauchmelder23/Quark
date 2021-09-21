#pragma once

#include <sstream>
#include "Event.hpp"

namespace Quark
{
	/// <summary>
	/// Event for when the mouse was moved
	/// </summary>
	class QUARK_API MouseMovedEvent : public Event
	{
	public:
		/// <summary>
		/// Create event with the given parameters
		/// </summary>
		/// <param name="x">The new x coordinate of the mouse</param>
		/// <param name="y">The new y coordinate of the mouse</param>
		MouseMovedEvent(float x, float y) :
			m_MouseX(x), m_MouseY(y) {}

		/// <summary>
		/// Get the mouse x coordinate
		/// </summary>
		/// <returns>The mouse x coordinate</returns>
		inline float GetX() const { return m_MouseX; }

		/// <summary>
		/// Get the mouse y coordinate
		/// </summary>
		/// <returns>The mouse y coordinate</returns>
		inline float GetY() const { return m_MouseY; }

		/// <summary>
		/// Convenience function for printing event details
		/// </summary>
		/// <returns>Formatted string with event data</returns>
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY;
	};

	/// <summary>
	/// Event for when the mouse wheel was used
	/// </summary>
	class QUARK_API MouseScrolledEvent : public Event
	{
	public:
		/// <summary>
		/// Create new event with given parameters
		/// </summary>
		/// <param name="OffsetX">How far the mouse wheel was scrolled</param>
		/// <param name="OffsetY">How far the mouse wheel was tilted horizontally</param>
		MouseScrolledEvent(float OffsetX, float OffsetY) :
			m_OffsetX(OffsetX), m_OffsetY(OffsetY) {}

		/// <summary>
		/// Get the scroll distance
		/// </summary>
		/// <returns>How far and in which direction the wheel was scrolled</returns>
		inline float GetOffsetX() const { return m_OffsetX; }

		/// <summary>
		/// Get the mouse wheel tilt direction
		/// </summary>
		/// <returns>How far and in which direction the wheel was tilted</returns>
		inline float GetOffsetY() const { return m_OffsetY; }

		/// <summary>
		/// Convenience function for printing event details
		/// </summary>
		/// <returns>Formatted string with event data</returns>
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_OffsetX << ", " << m_OffsetY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_OffsetX, m_OffsetY;
	};

	/// <summary>
	/// Base class for all mouse button related events
	/// </summary>
	class QUARK_API MouseButtonEvent : public Event
	{
	public:
		/// <summary>
		/// Returns the interacted mouse button
		/// </summary>
		/// <returns>The mouse button in question</returns>
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		/// <summary>
		/// Create new event with the given parameters
		/// </summary>
		/// <param name="button">The interacted mouse button</param>
		MouseButtonEvent(int button) :
			m_Button(button) {}

		int m_Button;
	};

	/// <summary>
	/// Event for when a mouse button was pressed
	/// </summary>
	class QUARK_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		/// <summary>
		/// Create new event with given parameters
		/// </summary>
		/// <param name="button">The pressed mouse button</param>
		MouseButtonPressedEvent(int button) :
			MouseButtonEvent(button) {}

		/// <summary>
		/// Convenience function for printing event details
		/// </summary>
		/// <returns>Formatted string with event data</returns>
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};
	
	/// <summary>
	/// Event for when a mouse button was released
	/// </summary>
	class QUARK_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		/// <summary>
		/// Create new event with given parameters
		/// </summary>
		/// <param name="button">The released mouse button</param>
		MouseButtonReleasedEvent(int button) :
			MouseButtonEvent(button) {}

		/// <summary>
		/// Convenience function for printing event details
		/// </summary>
		/// <returns>Formatted string with event data</returns>
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}
