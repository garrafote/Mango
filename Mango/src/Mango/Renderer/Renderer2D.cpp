#include "MangoPCH.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Mango {

	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> UnlitShader;
		Ref<Texture> WhiteTexture;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();

		s_Data->QuadVertexArray = Mango::VertexArray::Create();

		float quadVertices[5 * 4] = {
			// position        | UV
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
		};

		Ref<Mango::VertexBuffer> quadVB;
		quadVB = VertexBuffer::Create(quadVertices, sizeof(quadVertices));
		quadVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" },
		});
		s_Data->QuadVertexArray->AddVertexBuffer(quadVB);

		unsigned int quadIndices[6]{ 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB;
		squareIB = IndexBuffer::Create(quadIndices, 6);
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

		s_Data->WhiteTexture = Texture2D::Create(1, 1);

		s_Data->UnlitShader = Shader::Create("assets/shaders/Unlit2D.glsl");
		s_Data->UnlitShader->Bind();
		s_Data->UnlitShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->UnlitShader->Bind();
		s_Data->UnlitShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Data->UnlitShader->SetFloat4("u_Color", color);
		s_Data->UnlitShader->SetFloat4("u_Tiling", { 1.0, 1.0, 0.0, 0.0 });
		s_Data->WhiteTexture->Bind();

		glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), position), { size.x, size.y, 1.0f });
		s_Data->UnlitShader->SetMat4("u_Model", transform);
		
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec2& tiling, const glm::vec2& offset)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tiling, offset);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec2& tiling, const glm::vec2& offset)
	{
		s_Data->UnlitShader->SetFloat4("u_Color", glm::vec4(1.0f));
		s_Data->UnlitShader->SetFloat4("u_Tiling", { tiling.x, tiling.y, offset.x, offset.y });
		texture->Bind();

		glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), position), { size.x, size.y, 1.0f });
		s_Data->UnlitShader->SetMat4("u_Model", transform);
		
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

}