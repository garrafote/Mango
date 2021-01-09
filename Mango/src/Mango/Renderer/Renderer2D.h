#pragma once

#include "Mango/Renderer/OrthographicCamera.h"

#include "Mango/Renderer/Texture.h"

namespace Mango {

	class Renderer2D
	{
	public:
		static void Init(); 
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec2& tiling = glm::vec2(1.0f), const glm::vec2& offset = glm::vec2(0.0f), const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec2& tiling = glm::vec2(1.0f), const glm::vec2& offset = glm::vec2(0.0f), const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec2& tiling = glm::vec2(1.0f), const glm::vec2& offset = glm::vec2(0.0f), const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec2& tiling = glm::vec2(1.0f), const glm::vec2& offset = glm::vec2(0.0f), const glm::vec4& tintColor = glm::vec4(1.0f));
	
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, const glm::vec4& tilingAndOffset = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f), const glm::vec4& tintColor = glm::vec4(1.0f));

	};

}

