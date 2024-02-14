#pragma once
#include "Component/Component.h"

namespace oxygen
{
	struct Mesh;
	struct StaticMeshComponent : Component
	{
		OXYGENOBJECT(StaticMeshComponent, Component);

		std::shared_ptr<Mesh> m_mesh{};
	};
}; // namespace oxygen