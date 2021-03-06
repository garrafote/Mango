#pragma once

#include "Mango/Renderer/Camera.h"
#include "Mango/Renderer/OrthographicCamera.h"

#include "Mango/Renderer/Texture.h"
#include "Mango/Renderer/SubTexture2D.h"
#include "Mango/Renderer/EditorCamera.h"

#include "Mango/Scene/Components.h"

namespace Mango {

	class Renderer2D
	{
	public:
		static void Init(); 
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const EditorCamera& camera);
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
	
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subtexture, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subtexture, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subtexture, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subtexture, const glm::vec4& tintColor = glm::vec4(1.0f));
	
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, const glm::vec4& tilingAndOffset = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f), const glm::vec4& tintColor = glm::vec4(1.0f), const glm::vec2* quadTexCoords = nullptr, int32_t entityId = -1);


		static void DrawSprite(const glm::mat4& transform, const SpriteRendererComponent& src, int32_t entityId);

		// Stats
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};

		static Statistics GetStats();
		static void ResetStats();

	private:
		static void Reset();
		static void FlushAndReset();
	};

}

