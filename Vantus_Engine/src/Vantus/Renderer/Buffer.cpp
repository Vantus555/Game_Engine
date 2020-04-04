#include "vpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Vantus {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::None: 
			VANTUS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL: 
			return new OpenGLVertexBuffer(vertices, size);
		}
		VANTUS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::None: 
			VANTUS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL: 
			return new OpenGLIndexBuffer(indices, size);
		}
		VANTUS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}