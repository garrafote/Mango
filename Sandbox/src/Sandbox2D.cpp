#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
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
		Mango::Renderer2D::ResetStats();
		Mango::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Mango::RenderCommand::Clear();
	}

	// Render Draw
	{
		MGO_PROFILE_SCOPE("Renderer Draw");
		Mango::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Mango::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.3f, 0.2f, 0.8f, 1.0f });
		Mango::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_Texture, { 10.0f, 10.0f });

		static float rotation = 0;
		rotation += ts.GetSeconds() * 10;
		Mango::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.1f }, { 0.8f, 0.8f }, glm::radians(rotation), m_Texture, {1.0f, 1.0f}, {0.0f, 0.0f}, m_SquareColor);

		Mango::Renderer2D::EndScene();


		Mango::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Mango::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Mango::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	MGO_PROFILE_FUNCTION();

	ImGui::Begin("Stats");
	auto stats = Mango::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("	Draw Calls:  %d", stats.DrawCalls);
	ImGui::Text("	Quads:  %d", stats.QuadCount);
	ImGui::Text("	Vertices:  %d", stats.GetTotalVertexCount());
	ImGui::Text("	Indices:  %d", stats.GetTotalIndexCount());
	ImGui::End();


	ImGui::Begin("Properties");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Mango::Event& e)
{
	m_CameraController.OnEvent(e);
}
