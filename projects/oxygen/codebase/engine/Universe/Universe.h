#pragma once

#include "Singleton/Singleton.h"

namespace oxygen
{
	struct World;
	struct Universe : ObjectSingletonBase<Universe, HardcodedObjectID_Universe>
	{
		OXYGENOBJECT(Universe, Object);

		auto SwapWorld(std::shared_ptr<World> world) -> void;
		auto GetWorld() const -> const std::shared_ptr<World>&
		{
			return m_world;
		}

	  private:
		std::shared_ptr<World> m_world{};
	};
}; // namespace oxygen