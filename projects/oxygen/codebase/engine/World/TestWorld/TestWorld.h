#pragma once

#include "World/World.h"

namespace oxygen
{
	struct TestWorld : World
	{
		OXYGENOBJECT(TestWorld, World);

		auto OnWorldStart() -> void override;
	};
}; // namespace oxygen