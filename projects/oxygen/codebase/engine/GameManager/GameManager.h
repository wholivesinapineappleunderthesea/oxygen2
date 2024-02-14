#pragma once

namespace oxygen
{
	struct GameManager : ObjectSingletonBase<GameManager, HardcodedObjectID_GameManager>
	{
		OXYGENOBJECT(GameManager, Object);

		auto StartGame() -> void;
		auto EndGame() -> void;
	};
}; // namespace oxygen