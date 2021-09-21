#pragma once

#include <sstream>
#include "Event.hpp"

namespace Quark
{
	/// <summary>
	/// Base class for all keyboard related events
	/// </summary>
	class QUARK_API KeyEvent : public Event
	{
	public:
		/// <summary>
		/// Every keyboard event will contain a keycode
		/// </summary>
		/// <returns>Keycode of the interacted key</returns>
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		/// <summary>
		/// Create new keyboard event with the given keycode
		/// </summary>
		KeyEvent(int keycode) :
			m_KeyCode(keycode) {}

		int m_KeyCode;
	};

	/// <summary>
	/// Event for when a key was pressed
	/// </summary>
	class QUARK_API KeyPressedEvent : public KeyEvent
	{
	public:
		/// <summary>
		/// Create a new event with the given parameters
		/// </summary>
		/// <param name="keycode">Keycode of the pressed key</param>
		/// <param name="repeatCount">When the key is held down, the amount of "ticks" the key has been held for</param>
		KeyPressedEvent(int keycode, int repeatCount) :
			KeyEvent(keycode), m_RepeatCount(repeatCount) { }

		/// <summary>
		/// Gets the amount of ticks the key was held down for
		/// </summary>
		/// <returns>Number of key repetitions</returns>
		inline int GetRepeatCount() const { return m_RepeatCount; }

		/// <summary>
		/// Convenience function for printing event details
		/// </summary>
		/// <returns>Formatted string with event data</returns>
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << "(" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};

	/// <summary>
	/// Event for when a key was released
	/// </summary>
	class QUARK_API KeyReleasedEvent : public KeyEvent
	{
	public:
		/// <summary>
		/// Create new event with given parameters
		/// </summary>
		/// <param name="keycode">Keycode of the released key</param>
		KeyReleasedEvent(int keycode) :
			KeyEvent(keycode) { }

		/// <summary>
		/// Convenience function for printing event details
		/// </summary>
		/// <returns>Formatted string with event data</returns>
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}
