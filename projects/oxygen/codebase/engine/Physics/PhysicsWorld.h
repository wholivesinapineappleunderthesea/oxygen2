#pragma once

namespace oxygen
{
	struct PhysicsWorld : Object
	{
		OXYGENOBJECT(PhysicsWorld, Object);


		auto Step(float deltaTime) -> void;
	};
};