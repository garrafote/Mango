#include "SceneHierarchyPanel.h"

#include "Mango/Scene/Components.h"

#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>

namespace Mango {
	
	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		m_Context->m_Registry.each([&](auto e)
		{
			Entity entity = { e, m_Context.get() };
			DrawEntityNode(entity);
		});

		if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered())
			m_SelectionContext = {};

		ImGui::End();
		
		ImGui::Begin("Properties");

		if (m_SelectionContext)
		{
			DrawComponents(m_SelectionContext);
		}

		ImGui::End();
	}
	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;
		ImGuiBackendFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
		if (m_SelectionContext == entity) flags |= ImGuiTreeNodeFlags_Selected;
		bool expanded = ImGui::TreeNodeEx((void*)(uint32_t)entity, flags, tag.c_str());

		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		if (expanded)
		{
			ImGui::Text("Children...");
			ImGui::TreePop();
		}
	}

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;

			char buffer[64];
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}
		
		if (entity.HasComponent<TransformComponent>() && 
			ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
		{

			auto& transform = entity.GetComponent<TransformComponent>().Transform;
			
			ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);
			ImGui::TreePop();
		}
		
		if (entity.HasComponent<CameraComponent>() && 
			ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
		{
			auto& cameraComponent = entity.GetComponent<CameraComponent>();
			auto& camera = cameraComponent.Camera;

			const char* projectionTypeStrings[] = {"Perspective", "Orthographic"};
			const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];

			if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
			{
				for (int i = 0; i < 2; i++)
				{
					bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
					if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
					{
						currentProjectionTypeString = projectionTypeStrings[i];
						camera.SetProjectionType((SceneCamera::ProjectionType)i);
					}

					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}

			if (cameraComponent.Camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
			{
				float fov = glm::degrees(camera.GetPersectiveVerticalFOV());
				if (ImGui::DragFloat("Vertical FOV", &fov))
					camera.SetPerspectiveSize(glm::radians(fov));

				float orthoNear = camera.GetPerspectiveNearClip();
				if (ImGui::DragFloat("Near", &orthoNear))
					camera.SetPerspectiveNearClip(orthoNear);
				
				float orthoFar = camera.GetPerspectiveFarClip();
				if (ImGui::DragFloat("Far", &orthoFar))
					camera.SetPerspectiveFarClip(orthoFar);
			}

			if (cameraComponent.Camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
			{
				float size = camera.GetOrthographicSize();
				if (ImGui::DragFloat("Size", &size))
					camera.SetOrthographicSize(size);

				float perspectiveNear = camera.GetOrthographicNearClip();
				if (ImGui::DragFloat("Near", &perspectiveNear))
					camera.SetOrthographicNearClip(perspectiveNear);
				
				float perspectiveFar = camera.GetOrthographicFarClip();
				if (ImGui::DragFloat("Far", &perspectiveFar))
					camera.SetOrthographicFarClip(perspectiveFar);
			}

			ImGui::TreePop();
		}



	}
}