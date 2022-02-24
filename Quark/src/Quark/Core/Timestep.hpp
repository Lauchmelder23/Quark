#pragma once

#include <chrono>

#include <Quark/Core/Namespace.hpp>

QK_BEGIN

	/**
	 * @brief Represents a period of time
	 * 
	 * Typically used to communicate delta time between frames
	 */
	class Timestep
	{
	public:
		/**
		 * @brief Construct new Timestep from given duration
		 * 
		 * @param time The duration to store
		 */
		Timestep(std::chrono::duration<float> time) :
			m_Time(time)
		{

		}

		/**
		 * @brief Returns the duration with a given unit
		 * 
		 * @tparam Period The desired unit of time
		 * @return The period of time with the given unit as a float
		 */
		template<typename Period>
		inline float GetTimestep() const { return std::chrono::duration_cast<std::chrono::duration<float, Period>>(m_Time).count(); }

		/**
		 * @brief Returns time in seconds
		 */
		operator float() const { return m_Time.count(); }

		/**
		 * @brief Returns time in seconds
		 */
		inline float GetSeconds() const { return m_Time.count(); }
		
		/**
		 * @brief Returns time in milliseconds
		 */
		inline float GetMilliseconds() const { return GetTimestep<std::milli>(); }

	private:
		std::chrono::duration<float> m_Time;
	};

QK_END