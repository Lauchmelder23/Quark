#pragma once 

#include "Core.hpp"

#include "Quark/KeyCodes.hpp"
#include "Quark/MouseButtonCodes.hpp"

namespace Quark
{
	/**
	 * @brief A static interface for polling input
	 */
	class QUARK_API Input
	{
	public:
		/**
		 * @brief   Queries the state of the given key
		 * 
		 * @param   keycode The key to test for 
		 * @returns \c True if the specified key is currently pressed
		 */
		inline static bool IsKeyPressed(Key keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		/**
		 * @brief   Queries the state of the given mouse button
		 *
		 * @param   button The button to test for
		 * @returns \c True if the button key is currently pressed
		 */
		inline static bool IsMouseButtonPressed(MouseButton button) { return s_Instance->IsMouseButtonPressedImpl(button); }

		/**
		 * @brief   Queries the x coordiante of the mouse
		 *
		 * @returns x coordinate of the cursor
		 */
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }

		/**
		 * @brief   Queries the y coordiante of the mouse
		 *
		 * @returns y coordinate of the cursor
		 */
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		/** 
		 * @brief   Returns the current mouse position
		 * 
		 * @returns A pair of numbers representing the current mouse coordinate
		 */
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

	protected:
		/**
		 * @brief   Platform dependent implementation of IsKeyPressed()
		 *
		 * @param   keycode The key to test for 
		 * @returns \c True if the specified key is currently pressed
		 */
		virtual bool IsKeyPressedImpl(Key keycode) = 0;

		/**
		 * @brief   Platform dependent implementation of IsMouseButtonPressed()
		 *
		 * @param   button The key to test for
		 * @returns \c True if the specified button is currently pressed
		 */
		virtual bool IsMouseButtonPressedImpl(MouseButton button) = 0;

		/**
		 * @brief   Platform dependent implementation of GetMouseX()
		 *
		 * @returns x coordinate of the cursor
		 */
		virtual float GetMouseXImpl() = 0;

		/**
		 * @brief   Platform dependent implementation of GetMouseY()
		 *
		 * @returns y coordinate of the cursor
		 */
		virtual float GetMouseYImpl() = 0;

		/**
		 * @brief   Platform dependent implementation of GetMousePosition()
		 *
		 * @returns A pair of numbers representing the current mouse coordinate
		 */
		virtual std::pair<float, float> GetMousePositionImpl() = 0;

	private:
		static Input* s_Instance;
	};
}