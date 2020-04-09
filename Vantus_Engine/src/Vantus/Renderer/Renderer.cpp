#include "vpch.h"
#include "Renderer.h"

namespace Vantus {

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray) {
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}