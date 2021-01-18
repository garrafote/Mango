#include "MangoPCH.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Mango {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		MGO_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		MGO_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MGO_CORE_ASSERT(status, "Failed to initialize Glad!");

		MGO_CORE_INFO("OpenGL Info:");
		MGO_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		MGO_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		MGO_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

#ifdef MANGO_ENABLE_ASSERTS
		MGO_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Mango requires at least OpenGL version 4.5!");
#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		MGO_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}
