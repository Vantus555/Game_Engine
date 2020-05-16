#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Vantus/Core/TimeStep.h"

namespace Vantus {
	class VANTUS_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(TimeStep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() { return m_DebugName;  }
	private:
		std::string m_DebugName;
	};
}