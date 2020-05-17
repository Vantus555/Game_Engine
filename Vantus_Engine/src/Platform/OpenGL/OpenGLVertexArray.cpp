#include "vpch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Vantus {

	static GLenum ShaderDataTypeToGLBaseType(ShaderDataType type) {
		switch (type) {
		case Vantus::ShaderDataType::None:		return GL_FLOAT;
		case Vantus::ShaderDataType::Float:		return GL_FLOAT;
		case Vantus::ShaderDataType::Float2:	return GL_FLOAT;
		case Vantus::ShaderDataType::Float3:	return GL_FLOAT;
		case Vantus::ShaderDataType::Float4:	return GL_FLOAT;
		case Vantus::ShaderDataType::Mat3:		return GL_FLOAT;
		case Vantus::ShaderDataType::Mat4:		return GL_FLOAT;
		case Vantus::ShaderDataType::Int:		return GL_INT;
		case Vantus::ShaderDataType::Int2:		return GL_INT;
		case Vantus::ShaderDataType::Int3:		return GL_INT;
		case Vantus::ShaderDataType::Int4:		return GL_INT;
		case Vantus::ShaderDataType::Bool:		return GL_BOOL;
		}

		VANTUS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void Vantus::OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_RendererID);
	}

	void Vantus::OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void Vantus::OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
		VANTUS_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (auto& elem : layout) {
			glEnableVertexAttribArray(m_VertexArrayIndex);
			glVertexAttribPointer(m_VertexArrayIndex,
				elem.GetComponentCount(),
				ShaderDataTypeToGLBaseType(elem.Type),
				elem.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)elem.Offset);
			m_VertexArrayIndex++;
		}
		m_VertexBuffer.push_back(vertexBuffer);
	}

	void Vantus::OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}
