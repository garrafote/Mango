#include "MangoPCH.h"
#include "Entity.h"

namespace Mango {
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene) {}
}