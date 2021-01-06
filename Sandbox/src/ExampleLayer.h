#pragma once
#include "Mango.h"

class ExampleLayer : public Mango::Layer
{
public:
	ExampleLayer();

	void OnUpdate(Mango::Timestep ts) override;

	void OnImGuiRender() override;

	void OnEvent(Mango::Event& e) override;

private:
	Mango::ShaderLibrary m_ShaderLibrary;

	Mango::Ref<Mango::Shader> m_Shader;
	Mango::Ref<Mango::VertexArray> m_VertexArray;

	Mango::Ref<Mango::Shader> m_FlatColorShader;
	Mango::Ref<Mango::VertexArray> m_SquareVA;

	Mango::Ref<Mango::Texture2D> m_Texture;
	Mango::Ref<Mango::Texture2D> m_MangoLogoTexture;

	Mango::OrthographicCameraController m_CameraController;

	// Properties
	glm::vec3 m_SquareColor = { 0.8f, 0.2f, 0.3f };
};

