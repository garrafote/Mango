#include "Sandbox2D.h"

#include "Mango/Debug/Instrumentor.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>


static const uint32_t s_MapWidth = 24;
static const char* s_MapTiles =
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWDDDDDDDWDDDDDWWWWWW"
"WWWDDDDDDDDDDDDDDDDWWWWW"
"WWDDDWWDDDDDDDDDDDDDWWWW"
"WWDDWWWWDDDDDDDDDDDDDWWW"
"WWDDDDWDDDDDDDDDDDDDDDWW"
"WWDDDDDDDDDDDDDDDDDDDDWW"
"WWWDDDDDDDDDDDDDDDDDDWWW"
"WWWDDDDDDDDDDDDDDDDWWWWW"
"WWWWWDDDDDDDDDDDWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
;

SandboxLayer::SandboxLayer()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true), m_ParticleSystem(10000)
{
}

void SandboxLayer::OnAttach()
{
	MGO_PROFILE_FUNCTION();

	Mango::FramebufferSpecification fbspec;
	fbspec.Width = 1280;
	fbspec.Height = 720;
	m_Framebuffer = Mango::Framebuffer::Create(fbspec);

	m_CheckerboardTexture = Mango::Texture2D::Create("assets/textures/Checkerboard.png");
	m_Spritesheet = Mango::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");
	m_StairsSprite = Mango::SubTexture2D::CreateFromCoords(m_Spritesheet, { 7, 6 }, glm::vec2(128));
	m_BarrelSprite = Mango::SubTexture2D::CreateFromCoords(m_Spritesheet, { 8, 2 }, glm::vec2(128));
	m_TreeSprite = Mango::SubTexture2D::CreateFromCoords(m_Spritesheet, { 2, 1 }, glm::vec2(128), { 1, 2 });

	m_MapWidth = s_MapWidth;
	m_MapHeight = strlen(s_MapTiles) / m_MapWidth;

	m_TextureMap['D'] = Mango::SubTexture2D::CreateFromCoords(m_Spritesheet, { 6, 11 }, glm::vec2(128));
	m_TextureMap['W'] = Mango::SubTexture2D::CreateFromCoords(m_Spritesheet, { 11, 11 }, glm::vec2(128));
	
	// Init here
	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 5.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };

	m_CameraController.SetZoomLevel(5);
}

void SandboxLayer::OnDettach()
{
	MGO_PROFILE_FUNCTION();

}

void SandboxLayer::OnUpdate(Mango::Timestep ts)
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
#if 1
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
	#else
		Mango::Renderer2D::BeginScene(m_CameraController.GetCamera());

		for (uint32_t y = 0; y < m_MapHeight; y++)
		{
			for (uint32_t x = 0; x < m_MapWidth; x++)
			{
				char tileType = s_MapTiles[x + y * m_MapWidth];
				Mango::Ref<Mango::SubTexture2D> texture;

				if (m_TextureMap.find(tileType) != m_TextureMap.end())
				{
					texture = m_TextureMap[tileType];
				}
				else
				{
					texture = m_BarrelSprite;
				}
				Mango::Renderer2D::DrawQuad({ x - m_MapWidth / 2.0f, m_MapHeight / 2.0f - y }, { 1.0f, 1.0f }, texture);
			}
		}

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
#endif
	}
}

void SandboxLayer::OnImGuiRender()
{
	MGO_PROFILE_FUNCTION();

	ImGui::Begin("Stats");
	auto stats = Mango::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("	Draw Calls:  %d", stats.DrawCalls);
	ImGui::Text("	Quads:  %d", stats.QuadCount);
	ImGui::Text("	Vertices:  %d", stats.GetTotalVertexCount());
	ImGui::Text("	Indices:  %d", stats.GetTotalIndexCount());
	
	ImGui::Text("Scene Properties:");
	uint32_t textureID = m_Framebuffer->GetColorAttachmentID();
	ImGui::Image((void*)textureID, ImVec2{ 1280.0f, 720.0f });
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();

}

void SandboxLayer::OnEvent(Mango::Event& e)
{
	m_CameraController.OnEvent(e);
}
