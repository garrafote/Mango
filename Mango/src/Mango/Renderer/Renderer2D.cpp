#include "MangoPCH.h"
#include "Renderer2D.h"

#include "Mango/Renderer/VertexArray.h"
#include "Mango/Renderer/Shader.h"
#include "Mango/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace Mango {

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		int32_t TexIndex;
		glm::vec4 Tiling;
		int32_t EntityId;
	};

	struct Renderer2DData
	{
		static const uint32_t MaxQuads = 10000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32; // TODO: RenderCaps

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> UnlitShader;
		Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1;

		glm::vec4 QuadVertexPositions[4] = {};

		Renderer2D::Statistics Stats;
	} s_Data;

	void Renderer2D::Init()
	{
		MGO_PROFILE_FUNCTION();

		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Int, "a_TexIndex" },
			{ ShaderDataType::Float4, "a_Tiling" },
			{ ShaderDataType::Int, "a_EntityId" },
		});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];
		for (uint32_t index = 0, offset = 0; index < s_Data.MaxIndices; index += 6, offset += 4)
		{
			quadIndices[index + 0] = offset + 0;
			quadIndices[index + 1] = offset + 1;
			quadIndices[index + 2] = offset + 2;

			quadIndices[index + 3] = offset + 2;
			quadIndices[index + 4] = offset + 3;
			quadIndices[index + 5] = offset + 0;
		}
		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		s_Data.WhiteTexture = Texture2D::Create(1, 1);

		s_Data.UnlitShader = Shader::Create("assets/shaders/Unlit2D.glsl");
		s_Data.UnlitShader->Bind();

		int32_t samplers[s_Data.MaxTextureSlots];
		for (int32_t index = 0; index < s_Data.MaxTextureSlots; index++)
			samplers[index] = index;
		s_Data.UnlitShader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);

		s_Data.TextureSlots[0] = s_Data.WhiteTexture;

		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::Shutdown()
	{
		MGO_PROFILE_FUNCTION();

		delete[] s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		MGO_PROFILE_FUNCTION();

		s_Data.UnlitShader->Bind();
		s_Data.UnlitShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		Reset();
	}

	void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		MGO_PROFILE_FUNCTION();

		glm::mat4 proj = camera.GetProjection();
		glm::mat4 view = glm::inverse(transform);

		glm::mat4 viewProj = camera.GetProjection() * glm::inverse(transform);

		s_Data.UnlitShader->Bind();
		s_Data.UnlitShader->SetMat4("u_ViewProjection", viewProj);

		Reset();
	}

	void Renderer2D::BeginScene(const EditorCamera& camera)
	{
		MGO_PROFILE_FUNCTION();
		
		glm::mat4 proj = camera.GetProjection();
		glm::mat4 view = camera.GetViewMatrix();

		glm::mat4 viewProj = camera.GetViewProjection();
		s_Data.UnlitShader->Bind();
		s_Data.UnlitShader->SetMat4("u_ViewProjection", viewProj);

		Reset();
	}

	void Renderer2D::EndScene()
	{
		MGO_PROFILE_FUNCTION();

		Flush();
	}

	void Renderer2D::Flush()
	{
		MGO_PROFILE_FUNCTION();

		size_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

		for (uint32_t index = 0; index < s_Data.TextureSlotIndex; index++)
		{
			s_Data.TextureSlots[index]->Bind(index);
		}

		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
		s_Data.Stats.DrawCalls++;
	}

	void Renderer2D::Reset()
	{
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::FlushAndReset()
	{
		Flush();
		Reset();
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position, 0.0f), size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		glm::mat4 transform(1.0f);
		transform = glm::translate(transform, position);
		transform = glm::scale(transform, { size, 1.0f });
		DrawQuad(transform, s_Data.WhiteTexture, { 1.0f, 1.0f, 0.0f, 0.0f }, color);
	}


	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position, 0.0f), size, rotation, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		glm::mat4 transform(1.0f);
		transform = glm::translate(transform, position);
		transform = glm::rotate(transform, rotation, { 0.0f, 0.0f, 1.0f });
		transform = glm::scale(transform, { size, 1.0f });
		DrawQuad(transform, s_Data.WhiteTexture, { 1.0f, 1.0f, 0.0f, 0.0f }, color);
	}


	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec2& tiling, const glm::vec2& offset, const glm::vec4& tintColor)
	{
		DrawQuad(glm::vec3(position, 0.0f), size, texture, tiling, offset);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec2& tiling, const glm::vec2& offset, const glm::vec4& tintColor)
	{
		glm::mat4 transform(1.0f);
		transform = glm::translate(transform, position);
		transform = glm::scale(transform, { size, 1.0f });
		DrawQuad(transform, texture, glm::vec4(tiling, offset), tintColor);
	}


	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec2& tiling, const glm::vec2& offset, const glm::vec4& tintColor)
	{
		DrawQuad(glm::vec3(position, 0.0f), size, rotation, texture, tiling, offset);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec2& tiling, const glm::vec2& offset, const glm::vec4& tintColor)
	{
		glm::mat4 transform(1.0f);
		transform = glm::translate(transform, position);
		transform = glm::rotate(transform, rotation, { 0.0f, 0.0f, 1.0f });
		transform = glm::scale(transform, { size, 1.0f });
		DrawQuad(transform, texture, glm::vec4(tiling, offset), tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subtexture, const glm::vec4& tintColor)
	{
		DrawQuad(glm::vec3(position, 0.0f), size, subtexture, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subtexture, const glm::vec4& tintColor)
	{
		glm::mat4 transform(1.0f);
		transform = glm::translate(transform, position);
		transform = glm::scale(transform, { size, 1.0f });
		DrawQuad(transform, subtexture->GetTexture(), glm::vec4(1.0f, 1.0f, 0.0f, 0.0f), tintColor, subtexture->GetTexCoords());
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subtexture, const glm::vec4& tintColor)
	{
		DrawQuad(glm::vec3(position, 0.0f), size, rotation, subtexture, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subtexture, const glm::vec4& tintColor)
	{
		glm::mat4 transform(1.0f);
		transform = glm::translate(transform, position);
		transform = glm::rotate(transform, rotation, { 0.0f, 0.0f, 1.0f });
		transform = glm::scale(transform, { size, 1.0f });
		DrawQuad(transform, subtexture->GetTexture(), glm::vec4(1.0f, 1.0f, 0.0f, 0.0f), tintColor, subtexture->GetTexCoords());
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color, int32_t entityId)
	{
		DrawQuad(transform, s_Data.WhiteTexture, glm::vec4(1.0f, 1.0f, 0.0f, 0.0f), color, nullptr, entityId);
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, const glm::vec4& tilingAndOffsett, const glm::vec4& tintColor, const glm::vec2* quadTexCoords, int32_t entityId)
	{
		MGO_PROFILE_FUNCTION();

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();

		int32_t textureIndex = -1;
		for (int32_t index = 0; index < static_cast<int32_t>(s_Data.TextureSlotIndex); index++)
		{
			if (*s_Data.TextureSlots[index] == *texture)
			{
				textureIndex = index;
				break;
			}
		}

		if (textureIndex == -1)
		{
			if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
				FlushAndReset();

			textureIndex = s_Data.TextureSlotIndex++;
			s_Data.TextureSlots[textureIndex] = texture;
		}

		constexpr glm::vec2 defaultTexCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const glm::vec2* texCoords = quadTexCoords ? quadTexCoords : defaultTexCoords;

		for (size_t index = 0; index < 4; index++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[index];
			s_Data.QuadVertexBufferPtr->Color = tintColor;
			s_Data.QuadVertexBufferPtr->TexCoord = texCoords[index];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->Tiling = tilingAndOffsett;
			s_Data.QuadVertexBufferPtr->EntityId = entityId;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}

	void Renderer2D::ResetStats()
	{
		memset(&s_Data.Stats, 0, sizeof(Renderer2D::Statistics));
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_Data.Stats;
	}
}
