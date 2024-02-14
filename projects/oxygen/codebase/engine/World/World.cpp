#include "OxygenPCH.h"
#include "World.h"
#include "Entity/Entity.h"
namespace oxygen
{
	auto World::CreateEntity() -> std::shared_ptr<Entity>
	{
		auto& om = ObjectManager::GetInstance();
		auto entity = om.CreateManagedObject<Entity>();
		entity->AddToWorld(*this);
		m_entities.push_back(entity);
		return entity;
	}
	auto World::DestroyEntity(Entity& entity) -> oxyBool
	{
		OXYCHECK(entity.m_world == this);
		for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
		{
			if (it->get() == &entity)
			{
				entity.RemoveFromWorld(*this);
				entity.Destroy();
				m_entities.erase(it);
				return true;
			}
		}
		return false;
	}
	auto World::OnWorldStart() -> void
	{
		m_worldTime = 0.0f;
	}
	auto World::OnWorldEnd() -> void
	{
		for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
		{
			auto& entity = *it;
			if (entity)
			{
				entity->RemoveFromWorld(*this);
				entity->Destroy();
			}
			it = m_entities.erase(it);
		}
	}
	auto World::Render(GfxRenderer& gfx) -> void
	{
		for (const auto& ref : m_entities)
		{
			auto& entity = *ref;
			if (entity.m_flags.m_isVisible && entity.m_flags.m_isActive)
			{
			}
		}
	}
	auto World::Update(oxyF32 deltaTime) -> void
	{
		m_worldTime += deltaTime;
	}
}; // namespace oxygen