#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// TODO: To be removed
#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
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

	Mango::Renderer2D::BeginScene(m_CameraController.GetCamera());
	
	Mango::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_SquareColor);

	Mango::Renderer2D::EndScene();
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
