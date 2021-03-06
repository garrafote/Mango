#include "MangoPCH.h"
#include "VertexArray.h"

#include "Mango/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Mango {
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    MGO_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		MGO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}