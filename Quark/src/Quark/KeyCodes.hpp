#pragma once

#include "Core.hpp"

QK_BEGIN

	/**
	 * @brief Defines Quark key codes
	 */
	enum class Key
	{
		Space,	
		Apostrophe,
		Comma,
		Minus,
		Period,
		Slash,
		Num0,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,
		Semicolon,
		Equal,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		LBracket,
		Backslash,
		RBracket,
		GraveAccent,
		World1,
		World2, 
		Escape,
		Enter,
		Tab,
		Backspace,
		Insert,
		Delete,
		Right,
		Left,
		Down,
		Up,
		PageUp,
		PageDown,
		Home,
		End,
		CapsLock,
		ScrollLock,
		NumLock,
		PrintScreen,
		Pause,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,
		F16,
		F17,
		F18,
		F19,
		F20,
		F21,
		F22,
		F23,
		F24,
		F25,
		NumPad0,
		NumPad1,
		NumPad2,
		NumPad3,
		NumPad4,
		NumPad5,
		NumPad6,
		NumPad7,
		NumPad8,
		NumPad9,
		NumPadDecimal,
		NumPadDivide,
		NumPadMultiply,
		NumPadSubtract,
		NumPadAdd,
		NumPadEnter,
		NumPadEqual,
		LeftShift,
		LeftControl,
		LeftAlt,
		LeftSuper,
		RightShift,
		RightControl,
		RightAlt,
		RightSuper,
		Menu,
		KeyCount,
		Unknown = -1,
	};

	/**
	 * @brief			Converts a Quark key code to the key code used by the underlying API (Win32, GLFW, ...)
	 * 
	 * @param keycode	A Quark key code
	 * @returns			The key code used by the underlying API
	 */
	QUARK_API inline int GetAPIKeyCode(Key keycode);

	/**
	 * @brief			Converts a key code used by the underlying API (Win32, GLFW, ...) to a Quark key code
	 *
	 * @param keycode	A key code used by the underlying API
	 * @returns			The Quark key code
	 */
	QUARK_API inline Key GetQuarkKeyCode(int keycode);

QK_END