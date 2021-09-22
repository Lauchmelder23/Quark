#pragma once

#include "Core.hpp"
#include "Events/Event.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Window.hpp"

namespace Quark
{
	/**
	 * @brief A structure containing everything needed to run the application.
	 */
	class QUARK_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		/**
		 * @brief Start the application; enter the program loop.
		 */
		void Run();

		/** 
		  * @brief   This function is called to catch any events sent out by Window
		  * 
		  * @param e The event to be handled
		  */
		void OnEvent(Event& e);

	private:
		/**
		 * @brief   Called internally when a WindowClose event is dispatched.
		 * 
		 * @returns \c True
		 */
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	/**
	 * @brief   Returns a pointer to an application. The user needs to
	 *		    implement this function in order to run their app.
	 * 
	 * @returns Pointer to an application
	 */
	Application* CreateApplication();

}