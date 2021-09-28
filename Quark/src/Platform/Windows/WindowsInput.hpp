#pragma once

#include "Quark/Input.hpp"

namespace Quark
{
	/**
	 * @brief Windows specific implementation of Input
	 * 
	 * Implements all purely virtual functions inside Input with
	 * windows specific code
	 */
	class WindowsInput final : public Input
	{
	protected:
		bool IsKeyPressedImpl(Key keycode) override;

		bool IsMouseButtonPressedImpl(MouseButton button) override;
		float GetMouseXImpl() override;
		float GetMouseYImpl() override;
		std::pair<float, float> GetMousePositionImpl() override;
	};
}