#pragma once

#include <sstream>
#include "Event.hpp"

namespace Quark
{
	/// <summary>
	/// 
	/// </summary>
	/**
	 * @brief Event for when the mouse was moved
	 */
	class QUARK_API MouseMovedEvent : public Event
	{
	public:
		/**
		 * @brief   Create event with the given parameters
		 * 
		 * @param x The new x coordinate of the mouse
		 * @param y The new y coordinate of the mouse
		 */
		MouseMovedEvent(float x, float y) :
			m_MouseX(x), m_MouseY(y) {}


		/**
		 * @brief   Get the mouse x coordinate
		 * 
		 * @returns The mouse x coordinate
		 */
		inline float GetX() const { return m_MouseX; }

		/**
		 * @brief   Get the mouse y coordinate
		 *
		 * @returns The mouse y coordinate
		 */
		inline float GetY() const { return m_MouseY; }


		/**
		 * @brief Convenience function for printing event details
		 * 
		 * @returns Formatted string with event data
		 */
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


	/**
	 * @brief Event for when the mouse wheel was used
	 */
	class QUARK_API MouseScrolledEvent : public Event
	{
	public:
		/**
		 * @brief         Create new event with given parameters
		 * 
		 * @param OffsetX How far the mouse wheel was scrolled
		 * @param OffsetY How far the mouse wheel was tilted horizontally
		 */
		MouseScrolledEvent(float OffsetX, float OffsetY) :
			m_OffsetX(OffsetX), m_OffsetY(OffsetY) {}


		/**
		 * @brief   Get the scroll distance
		 *
		 * @returns How far and in which direction the wheel was scrolled
		 */
		inline float GetOffsetX() const { return m_OffsetX; }

		/**
		 * @brief   Get the mouse wheel tilt direction
		 *
		 * @returns How far and in which direction the wheel was tilted
		 */
		inline float GetOffsetY() const { return m_OffsetY; }

		/**
		 * @brief   Convenience function for printing event details
		 *
		 * @returns Formatted string with event data
		 */
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


	/**
	 * @brief Base class for all mouse button related events
	 */
	class QUARK_API MouseButtonEvent : public Event
	{
	public:
		/**
		 * @brief   Returns the interacted mouse button
		 * 
		 * @returns The mouse button in question
		 */
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		/**
		 * @brief        Create new event with the given parameters
		 * 
		 * @param button The interacted mouse button
		 */
		MouseButtonEvent(int button) :
			m_Button(button) {}

		int m_Button;
	};


	/**
	 * @brief Event for when a mouse button was pressed
	 */
	class QUARK_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		/**
		 * @brief        Create new event with given parameters
		 * 
		 * @param button The pressed mouse button
		 */
		MouseButtonPressedEvent(int button) :
			MouseButtonEvent(button) {}

		/**
		 * @brief   Convenience function for printing event details
		 * 
		 * @returns Formatted string with event data
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};
	

	/**
	 * @brief Event for when a mouse button was released
	 */
	class QUARK_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		/**
		 * @brief        Create new event with given parameters
		 *
		 * @param button The released mouse button
		 */
		MouseButtonReleasedEvent(int button) :
			MouseButtonEvent(button) {}

		/**
		 * @brief   Convenience function for printing event details
		 *
		 * @returns Formatted string with event data
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}
