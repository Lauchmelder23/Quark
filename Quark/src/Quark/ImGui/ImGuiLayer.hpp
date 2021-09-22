#pragma once

#include "Quark/Core.hpp"
#include "Quark/Layer.hpp"
#include "Quark/Events/MouseEvent.hpp"
#include "Quark/Events/KeyEvent.hpp"
#include "Quark/Events/ApplicationEvent.hpp"

namespace Quark
{
	/**
	 * @brief A layer containing an ImGui context
	 * 
	 * This layer renders an ImGui window and handles all
	 * events that ImGui needs to function properly
	 */
	class QUARK_API ImGuiLayer : public Layer
	{
	public:
		/**
		 * @brief Create new layer
		 */
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;

	private:
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool OnMouseWheelScrolled(MouseScrolledEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnKeyDown(KeyPressedEvent& e);
		bool OnKeyUp(KeyReleasedEvent& e);
		bool OnKeyTyped(KeyTypedEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_Time = 0.0f;
	};
}