#pragma once 

#include "Core.hpp"
#include "Layer.hpp"

#include <vector>

QK_BEGIN

	/**
	 * @brief A structure containing a list of \ref Layer
	 * 
	 * During rendering the layer stack will render each layer, starting
	 * at the first element (so layers pushed onto the stack will be rendered last).
	 * Events are handled in reverse order, starting at the topmost layer and going
	 * down to the first layer that decides to handle the event. If no layer wants
	 * to handle the event it is discarded.
	 * 
	 * The stack is split into different sections:
	 *   - The default stack, which is generally used for actual game content
	 *   - The overlay stack, which is always rendered on top of the default stack. Typically used for menus, GUIs etc
	 * 
	 * If a layer is pushed to the layer stack, the stack also takes ownership of that layer.
	 * This means that if the layer stack gets deleted, it will also clean up  and destroy all
	 * layers it contains.
	 */
	class QUARK_API LayerStack
	{
	public:
		/**
		 * @brief Create a new layer stack
		 */
		LayerStack();

		/**
		 * @brief Destroy layer stack, delete all contained layers.
		 */
		~LayerStack();

		/**
		 * @brief       Push a Layer to the default layer stack
		 * 
		 * @param layer The layer that should be added
		 */
		void PushLayer(Layer* layer);

		/**
		 * @brief       Push a Layer to the overlay layer stack
		 *
		 * @param layer The layer that should be added
		 */
		void PushOverlay(Layer* overlay);

		/**
		 * @brief Pop a Layer from the default layer stack
		 */
		void PopLayer(Layer* layer);

		/**
		 * @brief Pop a Layer from the overlay layer stack
		 */
		void PopOverlay(Layer* overlay);

		/**
		 * @begin Get an iterator to the beginning of the stack
		 * 
		 * @returns A non-constant iterator to the beginning of the entire stack
		 */
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }

		/**
		 * @begin Get an iterator to the end of the stack
		 *
		 * @returns A non-constant iterator to the end of the entire stack
		 */
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

		/**
		 * @begin Get a reverse iterator to the end of the stack
		 *
		 * @returns A non-constant reverse iterator to the end of the entire stack
		 */
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }

		/**
		 * @begin Get a reverse iterator to the beginning of the stack
		 *
		 * @returns A non-constant reverse iterator to the beginning of the entire stack
		 */
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};

QK_END
