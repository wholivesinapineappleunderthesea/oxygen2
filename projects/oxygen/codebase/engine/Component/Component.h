#pragma once

namespace oxygen
{
	struct Entity;
	struct Component : ManagedObject
	{
		OXYGENOBJECT(Component, ManagedObject);

	  private:
		Entity* m_entity{};
		friend struct Entity;
	};
} // namespace oxygen