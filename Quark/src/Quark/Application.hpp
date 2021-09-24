#pragma once

#include "Core.hpp"

#include "Window.hpp"
#include "LayerStack.hpp"
#include "Events/Event.hpp"
#include "Events/ApplicationEvent.hpp"

#include "ImGui/ImGuiLayer.hpp"

namespace Quark
{
	/**
	 * @brief A singleton containing everything needed to run the application.
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

		/**
		 * @brief       Pushes a layer to the applications default layer stack
		 * 
		 * @param layer The layer to push
		 */
		void PushLayer(Layer* layer);

		/**
		 * @brief         Pushes a layer to the applications overlay layer stack
		 *
		 * @param overlay The layer to push
		 */
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		/**
		 * @brief   Called internally when a WindowClose event is dispatched.
		 * 
		 * @returns \c True
		 */
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	/**
	 * @brief   Returns a pointer to an application. The user needs to
	 *		    implement this function in order to run their app.
	 * 
	 * @returns Pointer to an application
	 */
	Application* CreateApplication();

}