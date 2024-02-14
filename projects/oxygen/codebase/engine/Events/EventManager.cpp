#include "OxygenPCH.h"
#include "EventManager.h"

namespace oxygen
{
	auto EventManager::RegisterListener(EventType type,
										EventCallbackType callback,
										void* userPointer) -> void
	{
		m_callbacksToRegister.emplace_back(
			type, std::make_pair(userPointer, callback));
	}

	auto EventManager::UnregisterListeners(EventType type,
										   EventCallbackType callback,
										   void* userPointer) -> void
	{
		m_callbacksToUnregister.emplace_back(
			type, std::make_pair(userPointer, callback));
	}

	auto EventManager::ProcessEvents(oxyS32 lim) -> void
	{
		ProcessCallbackAdditionAndRemoval();
		size_t max = m_eventQueue.size();
		if (lim != -1)
			max = lim;
		for (auto i = 0; i < max; ++i)
		{
			ProcessOneEvent();
		}
	}

	EventManager::~EventManager()
	{
		while (!m_eventQueue.empty())
		{
			delete m_eventQueue.top();
			m_eventQueue.pop();
		}
	}

	auto EventManager::ProcessCallbackAdditionAndRemoval() -> void
	{
		if (!m_callbacksToRegister.empty())
		{
			for (const auto& [type, cb] : m_callbacksToRegister)
			{
				m_eventCallbacks.emplace(type, cb);
			}
			m_callbacksToRegister.clear();
		}
		if (!m_callbacksToUnregister.empty())
		{
			for (const auto& [type, cb] : m_callbacksToUnregister)
			{
				const auto range = m_eventCallbacks.equal_range(type);
				for (auto it = range.first; it != range.second;)
				{
					if (it->second.first == cb.first &&
						it->second.second == cb.second)
					{
						it = m_eventCallbacks.erase(it);
					}
					else
					{
						++it;
					}
				}
			}
			m_callbacksToUnregister.clear();
		}
	}

	auto EventManager::ProcessOneEvent() -> void
	{
		if (m_eventQueue.empty())
			return;
		const auto event = m_eventQueue.top();
		m_eventQueue.pop();
		const auto range = m_eventCallbacks.equal_range(event->GetType());
		for (auto it = range.first; it != range.second; ++it)
		{
			const auto cb = it->second.second;
			if (cb)
				cb(it->second.first, *event);
		}
		delete event;
	}

}; // namespace oxygen