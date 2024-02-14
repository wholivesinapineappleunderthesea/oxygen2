#pragma once

namespace oxygen
{
	struct World;
	struct Component;
	struct Entity final : ManagedObject 
	{
		OXYGENOBJECT(Entity, ManagedObject);

		template <typename T>
		auto CreateComponent(oxyObjectID id = 0) -> std::shared_ptr<T>
			requires std::is_base_of_v<Component, T>;
		auto CreateComponent(const ObjectDescription& desc, oxyObjectID id = 0)
			-> std::shared_ptr<Component>;

		template <typename T>
		auto GetComponent() -> T*
			requires std::is_base_of_v<Component, T>;
		template <typename T, typename Fun>
		auto ForEachComponent(Fun&& fun) -> void
			requires std::is_base_of_v<Component, T> && std::invocable<Fun, T&>;

		

	  protected:
		virtual auto AddToWorld(World& world) -> void;
		virtual auto RemoveFromWorld(World& world) -> void;
		virtual auto Destroy() -> void;

		oxyVec3 m_position{};
		oxyQuat m_rotation{};
		oxyVec3 m_scale{1.0f, 1.0f, 1.0f};

		struct EntityFlags
		{
			oxyU32 m_isActive : 1 {};
			oxyU32 m_isStatic : 1 {};
			oxyU32 m_isVisible : 1 {};
			oxyU32 m_hasPhysics : 1 {};
		};
		EntityFlags m_flags{};
		World* m_world{};

		std::vector<std::shared_ptr<Component>> m_components{};

		friend struct World;
	};

	template <typename T>
	auto Entity::CreateComponent(oxyObjectID id) -> std::shared_ptr<T>
		requires std::is_base_of_v<Component, T>
	{
		auto& om = ObjectManager::GetInstance();
		auto ref = om.CreateManagedObject<T>(id);
		if (ref)
		{
			ref->m_entity = this;
			m_components.push_back(ref);
			return ref;
		}
		return nullptr;
	}

	template <typename T>
	auto Entity::GetComponent() -> T*
		requires std::is_base_of_v<Component, T>
	{
		for (const auto& componentRef : m_components)
		{
			auto& component = *componentRef;
			const auto casted = component.Cast<T>();
			if (casted)
				return casted;
		}
		return nullptr;
	}

	template <typename T, typename Fun>
	auto Entity::ForEachComponent(Fun&& fun) -> void
		requires std::is_base_of_v<Component, T> && std::invocable<Fun, T&>
	{
		for (const auto& componentRef : m_components)
		{
			auto& component = *componentRef;
			const auto casted = component.Cast<T>();
			if (casted)
				fun(*casted);
		}
	}
}; // namespace oxygen
