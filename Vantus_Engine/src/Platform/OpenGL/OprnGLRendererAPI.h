#pragma once
#include "Vantus/Renderer/RendererAPI.h"

namespace Vantus {

	class OprnGLRendererAPI : public RendererAPI {
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};

}
