#include "OxygenPCH.h"
#include "GameManager.h"

#include "Universe/Universe.h"

#include "World/TestWorld/TestWorld.h"

namespace oxygen
{

	auto GameManager::StartGame() -> void
	{
		auto world = ObjectManager::GetInstance().CreateManagedObject<TestWorld>();
		Universe::GetInstance().SwapWorld(world);
	}

	auto GameManager::EndGame() -> void
	{
	}

}; // namespace oxygen
