#include "OxygenPCH.h"
#include "Universe.h"

#include "World/World.h"

namespace oxygen
{
	auto Universe::SwapWorld(std::shared_ptr<World> world) -> void
	{
		if (m_world)
			m_world->OnWorldEnd();
		m_world = std::move(world);
		if (m_world)
			m_world->OnWorldStart();
	}
}; // namespace oxygen