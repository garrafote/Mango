#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	MGO_PROFILE_FUNCTION();

	m_Texture = Mango::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDettach()
{
	MGO_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Mango::Timestep ts)
{
	MGO_PROFILE_FUNCTION();

	// Update
	{
		MGO_PROFILE_SCOPE("Camera Controller Update");
		m_CameraController.OnUpdate(ts);
	}

	// Render Prep
	{
		MGO_PROFILE_SCOPE("Renderer Prep");
		Mango::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Mango::RenderCommand::Clear();
	}

	// Render Draw
	{
		MGO_PROFILE_SCOPE("Renderer Draw");
		Mango::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Mango::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 1.0f, 0.7f }, { 0.3f, 0.2f, 0.8f, 1.0f });
		Mango::Renderer2D::DrawQuad({ -0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture, { 10.0f, 10.0f }, { 0.0f, 0.0f }, { 0.6f, 0.2f, 0.8f, 1.0f });

		Mango::Renderer2D::DrawQuad({ -0.0f, 0.0f, 0.1f }, { 0.8f, 0.8f }, glm::radians(45.0f), m_SquareColor);

		Mango::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	MGO_PROFILE_FUNCTION();

	ImGui::Begin("Properties");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Mango::Event& e)
{
	m_CameraController.OnEvent(e);
}
