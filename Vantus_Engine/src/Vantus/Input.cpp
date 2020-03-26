#include "vpch.h"
#include "Vantus/Input.h"

namespace Vantus {

	inline bool Input::IsKeyPressed(int keycode) { 
		return s_Instance->IsKeyPressedImpl(keycode); 
	}

	inline bool Input::IsMouseButtonPressed(int button) { 
		return s_Instance->IsMouseButtonPressedImpl(button); 
	}

	inline std::pair<float, float> Input::GetMousePosition() { 
		return s_Instance->GetMousePositionImpl(); 
	}

	inline float Input::GetMouseX() { 
		return s_Instance->GetMouseXImpl(); 
	}

	inline float Input::GetMouseY() { 
		return s_Instance->GetMouseYImpl(); 
	}
}