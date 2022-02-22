#pragma once

#include "Quark/Core.hpp"
#include "qkpch.hpp"

QK_BEGIN

	/**
	 * @brief A structure containing all events currently supported by Quark.
	 */
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/**
	 * @brief Event categories supported by the engine. One type of
	 *		  event can belong to multiple event categories
	 */
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() { return EventType::type; }\
								EventType GetEventType() const override { return GetStaticType(); }\
								const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) int GetCategoryFlags() const override { return category; }

	/**
	 * @brief Base class for all events supported by the engine.
	 * 		  Defines several universal utility functions.
	 */
	class QUARK_API Event
	{
		friend class EventDispatcher;
	public:
		/**
		 * @brief   Returns the \ref EventType of this event
		 *
		 * @returns Type of the event
		 */
		virtual EventType GetEventType() const = 0;

		/**
		 * @brief   Returns a C-string containing the name of the event
		 * @see     ToString()
		 * 
		 * @returns C-String with event name
		 */
		virtual const char* GetName() const = 0;

		/**
		 * @brief   Returns the categories of this event
		 * 
		 * @returns Categories of this event as an integer
		 */
		virtual int GetCategoryFlags() const = 0;

		/**
		 * @brief   Returns a string containing the name of the event
		 * @see     GetName()
		 *
		 * @returns string with event name
		 */
		virtual std::string ToString() const { return GetName(); }


		/**
		 * @brief   Tests whether this event belongs to the given \ref EventCategory
		 * 
		 * @param   category Category to test against
		 * @returns \c True if this event belongs to \p category.
		 */
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

		bool Handled = false;	///< Whether the event has been handled or not
	};


	/**
	 * @brief Convenience class for sending events out to specified callback functions
	 */
	class EventDispatcher
	{
		/**
		 * @brief  Event callback function signature
		 * 
		 * @tparam T An event class
		 */
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		/**
		 * @brief Creates a new EventDispatcher containing the given Event
		 * 
		 * @param e Event the dispatcher will hold
		 */
		EventDispatcher(Event& e) :
			m_Event(e) { }

		/**
		 * @brief      Tries to dispatch the contained Event to the given callback function.
		 *             For this to succeed, the event types of the stored event and \p T must match.
		 * 			   
		 *             \c EventFn is a function pointer to a function with the signature \c bool(Event&)
		 * 
		 * @tparam     T \ref EventType the callback should be listening for
		 * @param func A callback function
		 * @returns    \c True if the event has been successfully dispatched and handled
		 */
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};


	/**
	 * @brief    Overload of the << operator
	 * 
	 * @param os Output stream 
	 * @param    e Event 
	 * @returns  The modified output stream
	 */
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

QK_END
