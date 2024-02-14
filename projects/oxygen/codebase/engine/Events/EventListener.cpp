#include "OxygenPCH.h"
#include "EventListener.h"
#include "EventManager.h"

namespace oxygen
{
	auto InternalRegisterEventListener(EventType type, void* object,
									   void (*callback)(void*, const Event&))
		-> void
	{
		EventManager::GetInstance().RegisterListener(type, callback, object);
	}
	auto InternalUnregisterEventListeners(EventType type, void* object,
										  void (*callback)(void*, const Event&))
		-> void
	{
		EventManager::GetInstance().UnregisterListeners(type, callback, object);
	}
}; // namespace oxygen
