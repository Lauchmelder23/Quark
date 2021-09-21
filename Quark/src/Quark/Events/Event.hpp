#pragma once

#include "Quark/Core.hpp"

#include <string>
#include <functional>

namespace Quark
{
	/// <summary>
	/// A structure containing all events currently supported by Quark
	/// </summary>
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/// <summary>
	/// Event categories supported by the engine. One type of
	/// event can belong to multiple event categories
	/// </summary>
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	/// <summary>
	/// Base class for all events supported by the engine.
	/// Defines several universal utility functions.
	/// </summary>
	class QUARK_API Event
	{
		friend class EventDispatcher;
	public:
		/// <summary>
		/// Returns the <see cref="EventType" /> of this event
		/// </summary>
		/// <returns>Type of the event</returns>
		virtual EventType GetEventType() const = 0;

		/// <summary>
		/// Returns a string containing the name of the event
		/// <seealso cref="ToString()" />
		/// </summary>
		/// <returns>String with event name</returns>
		virtual const char* GetName() const = 0;

		/// <summary>
		/// Returns the categories of this event
		/// </summary>
		/// <returns>Categories of this event as an integer</returns>
		virtual int GetCategoryFlags() const = 0;

		/// <summary>
		/// Returns a string containing the name of the event
		/// <seealso cref="GetName()" />
		/// </summary>
		/// <returns>String with event name</returns>
		virtual std::string ToString() const { return GetName(); }

		/// <summary>
		/// Tests whether this event belongs to the given <see cref="EventCategory"/>
		/// </summary>
		/// <param name="category">Category to test against</param>
		/// <returns><c>True</c>if this event belongs to <paramref name="category"/>.</returns>
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	protected:
		bool m_Handled = false;
	};

	/// <summary>
	/// Convenience class for sending events out to specified callback functions
	/// </summary>
	class EventDispatcher
	{
		/// <summary>
		/// Event callback function signature
		/// </summary>
		/// <typeparam name="T">An event class</typeparam>
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		/// <summary>
		/// Creates a new EventDispatcher containing the given <see cref="Event" />
		/// </summary>
		/// <param name="e"><see cref="Event" /> the dispatcher will hold</param>
		EventDispatcher(Event& e) :
			m_Event(e) { }

		/// <summary>
		/// Tries to dispatch the contained <see cref="Event" /> to the given callback function.
		/// For this to succeed, the event types of the stored event and <typeparamref name="T" /> must match.
		/// </summary>
		/// <remarks>
		/// <c>EventFn</c> is a function pointer to a function with the signature <c>bool(<see cref="Event"/>&amp;)</c>
		/// </remarks>
		/// <typeparam name="T"><see cref="EventType" /> the callback is listening for</typeparam>
		/// <param name="func">A callback function</param>
		/// <returns><c>true</c> if the event has been successfully dispatched. <c>false</c> if not.</returns>
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	/// <summary>
	/// Overload of the << operator
	/// </summary>
	/// <param name="os">Output stream</param>
	/// <param name="e">Event</param>
	/// <returns>The modified output stream</returns>
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
