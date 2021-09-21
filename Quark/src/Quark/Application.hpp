#pragma once

#include "Core.hpp"
#include "Events/Event.hpp"
#include "Window.hpp"

namespace Quark
{
	/// <summary>
	/// A structure containing everything needed to run the application
	/// </summary>
	class QUARK_API Application
	{
	public:
		Application();
		virtual ~Application();

		/// <summary>
		/// Start the application; enter the program loop
		/// </summary>
		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	/// <summary>
	/// Returns a pointer to an application. The user needs to
	/// implement this function in order to run their app.
	/// </summary>
	/// <returns>
	///	Pointer to an application
	/// </returns>
	Application* CreateApplication();

}