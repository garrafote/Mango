#include "MangoPCH.h"
#include "GraphicsContext.h"

#include "Mango/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Mango {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    MGO_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		MGO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
