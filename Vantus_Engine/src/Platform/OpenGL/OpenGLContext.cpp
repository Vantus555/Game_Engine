#include "vpch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Vantus {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		VANTUS_CORE_ASSERT(m_WindowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		VANTUS_CORE_ASSERT(status, "GLAD Error!");

		VANTUS_CORE_INFO("OpenGL info: ");
		VANTUS_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		VANTUS_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		VANTUS_CORE_INFO("	Version: {0}", glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}