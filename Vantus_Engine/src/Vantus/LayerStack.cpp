#include "vpch.h"
#include "LayerStack.h"

namespace Vantus {
	Vantus::LayerStack::LayerStack() {
	}

	Vantus::LayerStack::~LayerStack() {
		for (Layer* layer : m_Layer)
			delete layer;
	}

	void Vantus::LayerStack::PushLayer(Layer* layer) {
		m_Layer.emplace(m_Layer.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->OnAttach();
	}

	void Vantus::LayerStack::PushOverlay(Layer* overlay) {
		m_Layer.emplace_back(overlay);
		overlay->OnAttach();
	}

	void Vantus::LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_Layer.begin(), m_Layer.end(), layer);
		if (it != m_Layer.end()) {
			m_Layer.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void Vantus::LayerStack::PpoOverlay(Layer* overlay) {
		auto it = std::find(m_Layer.begin(), m_Layer.end(), overlay);
		if (it != m_Layer.end())
			m_Layer.erase(it);
	}
}
