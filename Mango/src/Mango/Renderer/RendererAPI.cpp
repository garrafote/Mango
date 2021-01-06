#include "MangoPCH.h"
#include "RendererAPI.h"

#include "Mango/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Mango {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
	
	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    MGO_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
		}

		MGO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
