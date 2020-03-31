#pragma once
#include "Vantus/Layer.h"
#include "Vantus/Events/ApplicationEvent.h"
#include "Vantus/Events/KeyEvent.h"
#include "Vantus/Events/MouseEvent.h"

namespace Vantus {

	class VANTUS_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0;
	};

}

