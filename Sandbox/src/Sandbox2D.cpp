#include "Sandbox2D.h"

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
	}
}

void Sandbox2D::OnImGuiRender()
{
	MGO_PROFILE_FUNCTION();


    // In 99% case you should be able to just call DockSpaceOverViewport() and ignore all the code below!
    // In this specific demo, we are not using DockSpaceOverViewport() because:
    // - we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
    // - we allow the host window to have padding (when opt_padding == true)
    // - we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport() in your code!)
    // TL;DR; this demo is more complicated than what you would normally use.
    // If we removed all the options we are showcasing, this demo would become:
    //     void ShowExampleAppDockSpace()
    //     {
    //         ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    //     }

	static bool dockspaceOpen = true;
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->GetWorkPos());
        ImGui::SetNextWindowSize(viewport->GetWorkSize());
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
			if (ImGui::MenuItem("Quit", "")) { Mango::Application::Get().Close(); }
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::End();
	ImGui::Begin("Stats");
	auto stats = Mango::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("	Draw Calls:  %d", stats.DrawCalls);
	ImGui::Text("	Quads:  %d", stats.QuadCount);
	ImGui::Text("	Vertices:  %d", stats.GetTotalVertexCount());
	ImGui::Text("	Indices:  %d", stats.GetTotalIndexCount());
	
	ImGui::Text("Scene Properties:");
	uint32_t textureID = m_CheckerboardTexture->GetRendererID();
	ImGui::Image((void*)textureID, ImVec2{ 256.0f, 256.0f });
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();

}

void Sandbox2D::OnEvent(Mango::Event& e)
{
	m_CameraController.OnEvent(e);
}
