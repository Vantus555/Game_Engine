#include "vpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OprnGLRendererAPI.h"

namespace Vantus {

	RendererAPI* RenderCommand::s_RendererAPI = new OprnGLRendererAPI;

}