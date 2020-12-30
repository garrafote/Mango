#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	m_QuadVA = Mango::VertexArray::Create();

	float quadVertices[4 * 3] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};

	Mango::Ref<Mango::VertexBuffer> quadVB;
	quadVB = Mango::VertexBuffer::Create(quadVertices, sizeof(quadVertices));
	quadVB->SetLayout({
		{ Mango::ShaderDataType::Float3, "a_Position" },
	});
	m_QuadVA->AddVertexBuffer(quadVB);

	unsigned int quadIndices[6]{ 0, 1, 2, 2, 3, 0 };
	Mango::Ref<Mango::IndexBuffer> squareIB;
	squareIB = Mango::IndexBuffer::Create(quadIndices, 6);
	m_QuadVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = Mango::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDettach()
{
}

void Sandbox2D::OnUpdate(Mango::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Mango::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Mango::RenderCommand::Clear();

	Mango::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(0.1f));

	m_FlatColorShader->Bind();
	std::dynamic_pointer_cast<Mango::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
	Mango::Renderer::Submit(m_FlatColorShader, m_QuadVA, glm::scale(glm::mat4(1), glm::vec3(1.5f)));

	Mango::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Properties");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Mango::Event& e)
{
	m_CameraController.OnEvent(e);
}
