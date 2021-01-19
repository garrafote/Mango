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
		void DrawComponent(Entity entity, const char* name, const std::function<void (T&)>& drawFunction)
		{
			if (entity.HasComponent<T>() &&
				ImGui::TreeNodeEx((void*)typeid(T).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, name))
			{
				auto& component = entity.GetComponent<T>();

				drawFunction(component);

				ImGui::TreePop();
			}
		}
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}
