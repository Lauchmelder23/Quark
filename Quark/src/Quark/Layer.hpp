#pragma once

#include "Core.hpp"
#include "Events/Event.hpp"

namespace Quark
{
	/**
	 * @brief Structure representing a Layer.
	 * 
	 * Layers are containers for graphics, event handlers, information etc. 
	 * They can be attached (i.e. pushed onto a LayerStack), which will let them
	 * display graphics or catch events. If a layer receives an Event it can
	 * decide to handle it, or let it pass through to the layer below
	 */
	class QUARK_API Layer
	{
	public:
		/**
		 * @brief      Create a new layer
		 * 
		 * @param name Debug name of the layer
		 */
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		/**
		 * @brief Gets called when the layer has been attached
		 */
		virtual void OnAttach() {}

		/**
		 * @brief Gets called when the layer has been detached
		 */
		virtual void OnDetach() {}

		/**
		 * @brief Gets called when the layer needs to update
		 */
		virtual void OnUpdate() {}

		/**
		 * @brief Gets called when the layer receives an event
		 */
		virtual void OnEvent(Event& event) {}

		/**
		 * @brief   Returns the debug name of the layer
		 * 
		 * @returns The debug name
		 */
		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}
