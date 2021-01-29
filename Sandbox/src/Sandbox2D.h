#pragma once
#include "Mango.h"

#include "ParticleSystem.h"

class SandboxLayer : public Mango::Layer
{
public:
	SandboxLayer();
	virtual ~SandboxLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDettach() override;
	
	virtual void OnUpdate(Mango::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Mango::Event& event) override;

private:

	Mango::OrthographicCameraController m_CameraController;

	Mango::Ref<Mango::Framebuffer> m_Framebuffer;

	Mango::Ref<Mango::Texture2D> m_CheckerboardTexture;
	Mango::Ref<Mango::Texture2D> m_Spritesheet;
	Mango::Ref<Mango::SubTexture2D> m_BarrelSprite, m_StairsSprite, m_TreeSprite;

	glm::vec4 m_SquareColor = { 0.8f, 0.2f, 0.3f, 0.8f };

	ParticleProps m_Particle;
	ParticleSystem m_ParticleSystem;

	std::unordered_map<char, Mango::Ref<Mango::SubTexture2D>> m_TextureMap;
	uint32_t m_MapWidth, m_MapHeight;
};

