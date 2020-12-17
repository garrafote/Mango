#include "MangoPCH.h"
#include "Shader.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Mango {
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    MGO_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		MGO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}