#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true), m_ParticleSystem(10000)
{
}

void Sandbox2D::OnAttach()
{
	MGO_PROFILE_FUNCTION();

	m_CheckerboardTexture = Mango::Texture2D::Create("assets/textures/Checkerboard.png");
	m_Spritesheet = Mango::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");
	m_StairsSprite = Mango::SubTexture2D::CreateFromCoords(m_Spritesheet, { 7, 6 }, glm::vec2(128));
	m_BarrelSprite = Mango::SubTexture2D::CreateFromCoords(m_Spritesheet, { 8, 2 }, glm::vec2(128));
	m_TreeSprite = Mango::SubTexture2D::CreateFromCoords(m_Spritesheet, { 2, 1 }, glm::vec2(128), { 1, 2 });
	
	// Init here
	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 5.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };
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
#if 0
		Mango::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Mango::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.3f, 0.2f, 0.8f, 1.0f });
		Mango::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, { 10.0f, 10.0f });

		static float rotation = 0;
		rotation += ts.GetSeconds() * 10;
		Mango::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.1f }, { 0.8f, 0.8f }, glm::radians(rotation), m_CheckerboardTexture, {1.0f, 1.0f}, {0.0f, 0.0f}, m_SquareColor);

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
#endif

		Mango::Renderer2D::BeginScene(m_CameraController.GetCamera());
	
		float tileOffsetX = 128.0f / (float)m_Spritesheet->GetWidth();
		float tileOffsetY = 128.0f / (float)m_Spritesheet->GetHeight();
		Mango::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.3f }, { 1.0f, 1.0f }, m_StairsSprite);
		Mango::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.3f }, { 1.0f, 1.0f }, m_BarrelSprite);
		Mango::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.3f }, { 1.0f, 2.0f }, m_TreeSprite);
		
		Mango::Renderer2D::EndScene();
		
		if (Mango::Input::IsMouseButtonPressed(MGO_MOUSE_BUTTON_LEFT))
		{
			auto [x, y] = Mango::Input::GetMousePosition();
			auto width = Mango::Application::Get().GetWindow().GetWidth();
			auto height = Mango::Application::Get().GetWindow().GetHeight();

			auto bounds = m_CameraController.GetBounds();
			auto pos = m_CameraController.GetCamera().GetPosition();
			x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
			y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
			m_Particle.Position = { x + pos.x, y + pos.y };
			for (int i = 0; i < 5; i++)
				m_ParticleSystem.Emit(m_Particle);
		}

		m_ParticleSystem.OnUpdate(ts);
		m_ParticleSystem.OnRender(m_CameraController.GetCamera());
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
