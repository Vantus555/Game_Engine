#include "vpch.h"
#include "OprnGLRendererAPI.h"

#include "glad/glad.h"

namespace Vantus {

	void OprnGLRendererAPI::SetClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OprnGLRendererAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OprnGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}