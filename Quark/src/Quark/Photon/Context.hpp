#pragma once

#include "Quark/Core.hpp"

QK_PHOTON_BEGIN

	/**
	* @brief A universal rendering context abstracting the underlying API
	*/
	class QUARK_API Context
	{
	public:
		/**
		* @brief   Create a new rendering context for the given window handle
		* 
		* @param   handle A valid window handle
		* @returns A new rendering context
		*/
		static Context* Create(std::any handle);

	public:
		/**
		* @brief Initializes a new rendering context
		* 
		* This function gets implemented in a derived class, and is then
		* responsible for setting up that classes rendering API's context
		*/
		virtual void Init() = 0;

		/**
		* @brief Displays the frame buffer
		* 
		* This function gets implemented in a derived class, and is then
		* responsible for performing everything that is needed to display
		* the current frame buffer on the screen.
		*/
		virtual void SwapBuffers() = 0;

		/**
		* @brief Tell the context that the framebuffer was resized
		*/
		inline void FrameBufferResized() { m_FrameBufferResized = true; }

	protected:
		bool m_FrameBufferResized = false;
	};

QK_PHOTON_END