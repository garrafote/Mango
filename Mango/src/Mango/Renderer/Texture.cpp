#include "MangoPCH.h"
#include "Texture.h"

#include "Mango/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Mango {

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height, glm::vec4 color)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    MGO_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(width, height, color);
		}

		MGO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
		return Ref<Texture2D>();
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    MGO_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(path);
		}

		MGO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
		return Ref<Texture2D>();
	}
}