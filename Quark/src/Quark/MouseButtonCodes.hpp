#pragma once

#include "Quark/Core/Namespace.hpp"

QK_BEGIN

	/**
	 * @brief Defines Quark mouse button codes
	 */
	 // TODO: For now this just defines each mouse button with their GLFW mouse button codes
	enum class MouseButton
	{
		Button1				= 0,
		Button2				= 1,
		Button3				= 2,
		Button4				= 3,
		Button5				= 4,
		Button6				= 5,
		Button7				= 6,
		Button8				= 7,
		Left				= Button1,
		Right				= Button2,
		Middle				= Button3,
		XButton1			= Button4,
		XButton2			= Button5,
		XButton3			= Button6,
		XButton4			= Button7,
		XButton5			= Button8,
		Last				= Button8
	};

	/**
	 * @brief			Converts a Quark mouse button code to the mouse button code used by the underlying API (Win32, GLFW, ...)
	 *
	 * @param button	A Quark mouse button code
	 * @returns			The mouse button code used by the underlying API
	 */
	QUARK_API inline int GetAPIMouseButtonCode(MouseButton button);

	/**
	 * @brief			Converts a Quark mouse button code to the mouse button code used by the underlying API (Win32, GLFW, ...)
	 *
	 * @param button	A Quark mouse button code
	 * @returns			The mouse button code used by the underlying API
	 */
	QUARK_API inline MouseButton GetQuarkMouseButtonCode(int button);

QK_END