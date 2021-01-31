#pragma once

#include "Mango.h"
#include "Panels/SceneHierarchyPanel.h"

#include "Mango/Renderer/EditorCamera.h"

namespace Mango {
	
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
		bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveSceneAs();

	private:

		Mango::OrthographicCameraController m_CameraController;

		Mango::Ref<Mango::Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;

		EditorCamera m_EditorCamera;

		Mango::Ref<Mango::Texture2D> m_CheckerboardTexture;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];

		glm::vec4 m_SquareColor = { 0.8f, 0.2f, 0.3f, 0.8f };

		int m_GizmoType = -1;

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};

}
