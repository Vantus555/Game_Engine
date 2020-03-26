#pragma once

#include "Vantus/Core.h"

namespace Vantus {
	class VANTUS_API Input {
	public:
		inline static bool IsKeyPressed(int keycode);
		inline static bool IsMouseButtonPressed(int button);
		inline static std::pair<float, float> GetMousePosition();
		inline static float GetMouseX();
		inline static float GetMouseY();
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Input* s_Instance;
	};
}