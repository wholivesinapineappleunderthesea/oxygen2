#pragma once

namespace oxygen
{
	struct Entity;
	struct GfxRenderer;
	struct World : ManagedObject
	{
		OXYGENOBJECT(World, ManagedObject);

		auto CreateEntity() -> std::shared_ptr<Entity>;
		auto DestroyEntity(Entity& entity) -> oxyBool;

		auto GetEntities() const -> std::span<const std::shared_ptr<Entity>>
		{
			return m_entities;
		}

	  protected:
		
		virtual auto OnWorldStart() -> void;
		virtual auto OnWorldEnd() -> void;
		virtual auto Render(GfxRenderer& gfx) -> void;
		virtual auto Update(oxyF32 deltaTime) -> void;
		
		friend struct Universe;
		friend struct GfxRenderer;

	  private:
		oxyF32 m_worldTime{};
		std::vector<std::shared_ptr<Entity>> m_entities;
	};
}; // namespace oxygen