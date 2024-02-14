#pragma once

#include "Filesystem/Filesystem.h"
#include "Object/ObjectManager.h"
#include "DebugCamera/DebugCamera.h"
#include "Events/EventManager.h"
#include "Input/InputManager.h"
#include "GfxRenderer/GfxRenderer.h"
#include "Universe/Universe.h"
#include "GameManager/GameManager.h"

namespace oxygen
{
	struct InternalOxygenSingletonsOrder
	{

		SingletonInstance<Filesystem> m_filesystem{};
		SingletonInstance<ObjectManager> m_objectManager{};
		SingletonInstance<DebugCamera> m_debugCamera{};
		SingletonInstance<EventManager> m_eventManager{};
		SingletonInstance<InputManager> m_inputManager{};
		SingletonInstance<GfxRenderer> m_gfxRenderer{};
		ObjectSingletonInstance<Universe> m_universe{};
		ObjectSingletonInstance<GameManager> m_gameManager{};
	};

	using OxygenSingletons = SingletonHolder<InternalOxygenSingletonsOrder>;
}; // namespace oxygen