#include "OxygenPCH.h"
#include "Entity.h"
#include "World/World.h"
#include "Component/Component.h"

namespace oxygen
{
	auto Entity::CreateComponent(const ObjectDescription& desc, oxyObjectID id)
		-> std::shared_ptr<Component>
	{
		auto& om = ObjectManager::GetInstance();
		auto ref = om.CreateManagedObject(desc, id);
		if (ref)
		{
			auto componentTypedRef =
				std::static_pointer_cast<Component>(std::move(ref));
			if (componentTypedRef)
			{
				componentTypedRef->m_entity = this;
				m_components.push_back(componentTypedRef);
				return componentTypedRef;
			}
		}
		return nullptr;
	}

	auto Entity::AddToWorld(World& world) -> void
	{
		OXYCHECK(!m_world);
		m_world = &world;
	}

	auto Entity::RemoveFromWorld(World& world) -> void
	{
		OXYCHECK(m_world);
		m_world = nullptr;
	}

	auto Entity::Destroy() -> void
	{
		if (m_world)
		{
			m_world->DestroyEntity(*this);
		}
	}

}; // namespace oxygen