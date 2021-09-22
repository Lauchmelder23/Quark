#include "LayerStack.hpp"

namespace Quark
{
	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer) + 1;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.push_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		std::vector<Layer*>::const_iterator it = std::find(m_Layers.begin(), m_LayerInsert, layer);
		if (it != m_LayerInsert)
		{
			m_Layers.erase(it);
			m_LayerInsert--;
		}
		layer->OnDetach();
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		std::vector<Layer*>::const_iterator it = std::find(m_LayerInsert, m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
		overlay->OnDetach();
	}
}
