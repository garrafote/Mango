#include "SceneHierarchyPanel.h"

#include "Mango/Scene/Components.h"

#include <imgui/imgui.h>

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
}