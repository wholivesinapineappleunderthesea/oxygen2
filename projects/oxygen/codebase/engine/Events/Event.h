#pragma once

namespace oxygen
{
	/**
	 * @brief Base class for all events.
	 * 	 
	 * @details Event are dispatched before the rest of the game logic is updated, you can easily register a callback to receive events by using the EventListener class.
	 * 
	*/
	struct Event
	{
		virtual ~Event() = default;
		virtual auto GetType() const -> EventType = 0;
		virtual auto GetPriority() const -> EventPriority
		{
			return EventPriority_Low;
		}
		virtual auto GetTypeStr() const -> const char* = 0;
		static inline auto GetStaticType() -> EventType
		{
			return EventType_Invalid;
		}
		static inline auto GetStaticTypeStr() -> const char*
		{
			return "Invalid";
		}
	};

#define DECLARE_EVENT_TYPE(SelfType)                                           \
	static inline auto GetStaticType()->EventType                              \
	{                                                                          \
		return EventType_##SelfType;                                           \
	}                                                                          \
	static inline auto GetStaticTypeStr()->const char*                         \
	{                                                                          \
		return #SelfType;                                                      \
	}                                                                          \
	auto GetType() const->EventType override                                   \
	{                                                                          \
		return GetStaticType();                                                \
	}                                                                          \
	auto GetTypeStr() const->const char* override                              \
	{                                                                          \
		return GetStaticTypeStr();                                             \
	}
#define DECLARE_EVENT_PRIORITY(Priority)                                       \
	auto GetPriority() const->EventPriority override                           \
	{                                                                          \
		return EventPriority_##Priority;                                       \
	}

	struct KeyboardButtonStateChangedEvent : Event
	{
		DECLARE_EVENT_TYPE(KeyboardButtonStateChangedEvent);
		KeyboardButton m_button{};
		oxyBool m_isDown{};
	};

	struct MouseButtonStateChangedEvent : Event
	{
		DECLARE_EVENT_TYPE(MouseButtonStateChangedEvent);
		MouseButton m_button{};
		oxyBool m_isDown{};
	};

	struct MouseMovedEvent : Event
	{
		DECLARE_EVENT_TYPE(MouseMovedEvent);
		oxyS32 m_x{};
		oxyS32 m_y{};
		oxyS32 m_prevX{};
		oxyS32 m_prevY{};
		oxyF32 m_dx{};
		oxyF32 m_dy{};
	};

	struct ControllerConnectionStateChangedEvent : Event
	{
		DECLARE_EVENT_TYPE(ControllerConnectionStateChangedEvent);
		oxyS32 m_controllerIndex{};
		oxyBool m_isConnected{};
	};

	struct ControllerAxisValueChangedEvent : Event
	{
		DECLARE_EVENT_TYPE(ControllerAxisValueChangedEvent);
		oxyS32 m_controllerIndex{};
		ControllerAxis m_axis{};
		oxyF32 m_value{};
		oxyF32 m_prevValue{};
	};

	struct ControllerButtonStateChangedEvent : Event
	{
		DECLARE_EVENT_TYPE(ControllerButtonStateChangedEvent);
		oxyS32 m_controllerIndex{};
		ControllerButton m_button{};
		oxyBool m_isDown{};
	};

	struct Scene;
	struct SceneChangedEvent : Event
	{
		DECLARE_EVENT_TYPE(SceneChangedEvent);
		std::shared_ptr<Scene> m_scene{};
	};
}; // namespace oxygen