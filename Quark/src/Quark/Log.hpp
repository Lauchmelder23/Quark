#pragma once

#include "Core.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Quark
{
	/// <summary>
	/// Static class containing basic logging functionality
	/// </summary>
	/// <remarks>
	///	The logging module contains two types of loggers:
	/// <list>
	///		<item><c>Core</c>, which is used internally</item>
	///		<item><c>Client</c>, which is for use by the application</item>
	/// </list>
	/// </remarks>
	
	/**
	 * @brief Static class containing basic logging functionality.
	 * 
	 * The logging module contains two types of loggers
	 *   - \c Core, which is used internally
	 *   - \c Client, which is for use by the application
	 */
	class QUARK_API Log
	{
	public:
		/**
		 * @brief Initialize the logging module.
		 */
		static void Init();

		/**
		 * @brief Returns the logger used internally used by the engine
		 * 
		 * @return A shared pointer to the core logger
		 */
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_CoreLogger; }

		/**
		 * @brief Returns the logger for use by the application
		 *
		 * @return A shared pointer to the client logger
		 */
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> m_CoreLogger;
		static std::shared_ptr<spdlog::logger> m_ClientLogger;
	};

}

#define QK_CORE_TRACE(...)      ::Quark::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define QK_CORE_INFO(...)       ::Quark::Log::GetCoreLogger()->info(__VA_ARGS__)
#define QK_CORE_WARN(...)       ::Quark::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define QK_CORE_ERROR(...)      ::Quark::Log::GetCoreLogger()->error(__VA_ARGS__)
#define QK_CORE_FATAL(...)      ::Quark::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define QK_TRACE(...)           ::Quark::Log::GetClientLogger()->trace(__VA_ARGS__)
#define QK_INFO(...)            ::Quark::Log::GetClientLogger()->info(__VA_ARGS__)
#define QK_WARN(...)            ::Quark::Log::GetClientLogger()->warn(__VA_ARGS__)
#define QK_ERROR(...)           ::Quark::Log::GetClientLogger()->error(__VA_ARGS__)
#define QK_FATAL(...)           ::Quark::Log::GetClientLogger()->critical(__VA_ARGS__)
