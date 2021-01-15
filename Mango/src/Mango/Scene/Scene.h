#pragma once

#include "Mango/Core/Timestep.h"

#include <entt.hpp>

namespace Mango {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());

		entt::registry& Reg() { return m_Registry; }
		
		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}
