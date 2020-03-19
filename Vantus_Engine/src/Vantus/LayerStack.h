#pragma once

#include "Core.h"
#include "Layer.h"

namespace Vantus {
	class VANTUS_API LayerStack {
	public:
		LayerStack();
		virtual ~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PpoOverlay(Layer* olerlay);

		std::vector<Layer*>::iterator begin() { return m_Layer.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layer.end(); }
	private:
		std::vector<Layer*> m_Layer;
		std::vector<Layer*>::iterator m_LayerInsert;
	};
}