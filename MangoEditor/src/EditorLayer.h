#pragma once
#include "Mango.h"

class EditorLayer : public Mango::Layer
{
public:
	EditorLayer();
	virtual ~EditorLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDettach() override;
	
	virtual void OnUpdate(Mango::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Mango::Event& event) override;

private:

	Mango::OrthographicCameraController m_CameraController;

	Mango::Ref<Mango::Framebuffer> m_Framebuffer;

	Mango::Ref<Mango::Texture2D> m_CheckerboardTexture;

	glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

	glm::vec4 m_SquareColor = { 0.8f, 0.2f, 0.3f, 0.8f };
};

