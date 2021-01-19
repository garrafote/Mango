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
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}
