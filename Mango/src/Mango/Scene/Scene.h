#pragma once

#include "Mango/Core/Timestep.h"

#include <entt.hpp>

namespace Mango {

	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		entt::registry& Reg() { return m_Registry; }
		
		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;
	};
}
