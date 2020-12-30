#pragma once
#include "Mango.h"

class Sandbox2D : public Mango::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDettach() override;
	
	virtual void OnUpdate(Mango::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Mango::Event& event) override;

private:

	Mango::OrthographicCameraController m_CameraController;

	// Temp
	Mango::Ref<Mango::Shader> m_FlatColorShader;
	Mango::Ref<Mango::Texture2D> m_Texture;
	Mango::Ref<Mango::VertexArray> m_QuadVA;

	glm::vec4 m_SquareColor = { 0.8f, 0.2f, 0.3f, 1.0f };
};
