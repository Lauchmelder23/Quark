#pragma once

#include "Quark/Input.hpp"

namespace Quark
{
	/**
	 *�@brief Windows specific implementation of Input
	 * 
	 * Implements all purely virtual functions inside Input with
	 * windows specific code
	 */
	class WindowsInput final : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
	};
}