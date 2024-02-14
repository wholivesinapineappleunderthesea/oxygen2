#pragma once

#include "Event.h"

namespace oxygen
{
	auto InternalRegisterEventListener(EventType type, void* object,
									   void (*callback)(void*, const Event&))
		-> void;
	auto InternalUnregisterEventListeners(EventType type, void* object,
										  void (*callback)(void*, const Event&))
		-> void;

	/**
	 * @brief Instantiating this class will register an event listener for the
	 * given event type. It will call the given member function passed in the
	 * template parameter when the event is triggered. Construct via passing in
	 * a pointer to the object that owns the member function.
	 * @tparam EventToListenTo The event type that this listener will listen to.
	 * @tparam MemberFunctionPtr The member function that will be called when
	 */
	template <EventType EventToListenTo, auto MemberFunctionPtr>
	struct EventListener : NonCopyable
	{
		template <typename T> struct ExtractMemberFunctionDetails;
		template <typename ObjectType, typename ReturnType, typename Arg1>
		struct ExtractMemberFunctionDetails<ReturnType (ObjectType::*)(Arg1)>
		{
			using object_type = ObjectType;
			using return_type = ReturnType;
			using arg_type = Arg1;
		};

		using FuncDetails =
			typename ExtractMemberFunctionDetails<decltype(MemberFunctionPtr)>;
		using ObjectType = FuncDetails::object_type;
		using EventParamType = FuncDetails::arg_type;

		EventListener(ObjectType* object) : m_objectPtr(object)
		{
			InternalRegisterEventListener(EventToListenTo, m_objectPtr,
										  &EventListener::Invoke);
		}
		~EventListener()
		{
			InternalUnregisterEventListeners(EventToListenTo, m_objectPtr,
											 &EventListener::Invoke);
		}
		static inline auto Invoke(void* object, const Event& event) -> void
		{
			const auto castedObject = static_cast<ObjectType*>(object);
			const auto castedEvent = static_cast<EventParamType>(event);
			(castedObject->*MemberFunctionPtr)(castedEvent);
		}
		ObjectType* m_objectPtr{};
	};
}; // namespace oxygen