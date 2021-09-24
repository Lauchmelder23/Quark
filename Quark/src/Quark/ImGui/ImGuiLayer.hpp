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

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}