#pragma once

#include "Singleton/Singleton.h"

#include "Event.h"

namespace oxygen
{
	/**
	 * @brief The EventManager class is responsible for managing the event queue
	 * and all callbacks. It is a singleton class, and can be accessed via
	 * EventManager::GetInstance().
	 */
	struct EventManager : SingletonBase<EventManager>
	{
		/**
		 * @brief The type of callback function that can be registered to listen
		 * to events. The first parameter is a user supplied pointer from when
		 * the callback was registered, the second parameter is the event that
		 * was triggered.
		 */
		using EventCallbackType = void (*)(void*, const Event&);

		/**
		 * @brief Used to register a callback for a given event type.
		 * EventListener wraps this into a more convenient pattern.
		 * @param type The event type to listen to.
		 * @param callback The callback function to call when the event is
		 * triggered.
		 * @param userPointer A user supplied pointer that will be passed to the
		 * callback.
		 */
		auto RegisterListener(EventType type, EventCallbackType callback,
							  void* userPointer) -> void;
		/**
		 * @brief Used to unregister a callback for a given event type. Pass in
		 * the same arguments that were passed to RegisterListener.
		 */
		auto UnregisterListeners(EventType type, EventCallbackType callback,
								 void* userPointer) -> void;

		/**
		 * @brief Submit an event to the event queue.
		 */
		template <typename EventT, typename... Args>
		auto QueueEvent(Args&&... args) -> void
		{
			static_assert(std::is_base_of_v<Event, EventT>,
						  "EventT must be derived from Event");
			const auto event = new EventT(std::forward<Args>(args)...);
			m_eventQueue.push(event);
		}

		/**
		 * @brief Process events in the queue. If lim is -1, then all events
		 * will be processed.
		 */
		auto ProcessEvents(oxyS32 lim = -1) -> void;

		~EventManager();
	  private:
		// Listeners:
		using MapValuePairType = std::pair<void*, EventCallbackType>;
		std::unordered_multimap<EventType, MapValuePairType> m_eventCallbacks{};
		// Callbacks could potentially be registered/unregistered during a
		// callback, these vectors will be used to instead delay the
		// insertion/removal in the map until ProcessEvents is called
		std::vector<std::pair<EventType, MapValuePairType>>
			m_callbacksToRegister{};
		std::vector<std::pair<EventType, MapValuePairType>>
			m_callbacksToUnregister{};
		auto ProcessCallbackAdditionAndRemoval() -> void;

		// Queue:
		// Must declare a comparison type for the priority queue
		struct PriorityQueueCompare
		{
			auto operator()(const Event* lhs, const Event* rhs) const -> bool
			{
				return lhs->GetPriority() < rhs->GetPriority();
			}
		};
		std::priority_queue<const Event*, std::vector<const Event*>,
							PriorityQueueCompare>
			m_eventQueue{};

		auto ProcessOneEvent() -> void;
	};
}; // namespace oxygen