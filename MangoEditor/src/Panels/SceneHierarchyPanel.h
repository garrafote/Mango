#pragma once

#include "Mango/Core/Base.h"
#include "Mango/Core/Log.h"
#include "Mango/Scene/Scene.h"
#include "Mango/Scene/Entity.h"

namespace Mango {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);

		template<typename T>
		void DrawComponent(Entity entity, const char* name, const std::function<void (T&)>& drawFunction, bool displayRemoveButton = true)
		{
			const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;

			if (entity.HasComponent<T>())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
				bool open =	ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name);
				ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
				if (ImGui::Button("+", ImVec2{ 20, 20 }))
				{
					ImGui::OpenPopup("ComponentSettings");
				}
				ImGui::PopStyleVar();

				bool componentRemoved = false;
				if (ImGui::BeginPopup("ComponentSettings"))
				{
					if (displayRemoveButton && ImGui::MenuItem("Remove Component"))
						componentRemoved = true;

					ImGui::EndPopup();
				}

				if (open)
				{
					auto& component = entity.GetComponent<T>();

					drawFunction(component);

					ImGui::TreePop();
				}

				if (componentRemoved)
					entity.RemoveComponent<T>();
			}
		}
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}
