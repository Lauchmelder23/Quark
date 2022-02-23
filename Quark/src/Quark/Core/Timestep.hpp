#pragma once

#include <chrono>

#include <Quark/Core/Namespace.hpp>

QK_BEGIN

	class Timestep
	{
	public:
		Timestep(std::chrono::duration<float> time) :
			m_Time(time)
		{

		}

		template<typename Period>
		inline float GetTimestep() const { return std::chrono::duration_cast<std::chrono::duration<float, Period>>(m_Time).count(); }

		operator float() const { return m_Time.count(); }

		inline float GetSeconds() const { return m_Time.count(); }
		inline float GetMilliseconds() const { return GetTimestep<std::milli>(); }

	private:
		std::chrono::duration<float> m_Time;
	};

QK_END