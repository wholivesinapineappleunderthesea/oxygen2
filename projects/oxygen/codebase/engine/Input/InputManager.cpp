#include "OxygenPCH.h"
#include "InputManager.h"

#include "Events/EventManager.h"

namespace oxygen
{
	auto InputManager::BeginUpdate(oxyF32 deltaTimeSeconds) -> void
	{
		m_lastUpdateState = m_state;
	}
	auto InputManager::UpdateController(oxyS32 index,
										const ControllerInputState& input)
		-> void
	{
		m_state.m_controllers[index] = input;
	}
	auto InputManager::UpdateMouse(const MouseInputState& input) -> void
	{
		m_state.m_mouse = input;
	}
	auto InputManager::UpdateKeyboard(const KeyboardInputState& input) -> void
	{
		m_state.m_keyboard = input;
	}
	auto InputManager::EndUpdate() -> void
	{
		auto& em = EventManager::GetInstance();

		for (oxyU8 i = KeyboardButton{}; i < KeyboardButton_Count; ++i)
		{
			const auto isDown = IsKeyDown(static_cast<KeyboardButton>(i));
			const auto wasDown = WasKeyDown(static_cast<KeyboardButton>(i));
			if (isDown != wasDown)
			{
				KeyboardButtonStateChangedEvent event{};
				event.m_button = static_cast<KeyboardButton>(i);
				event.m_isDown = isDown;
				em.QueueEvent<KeyboardButtonStateChangedEvent>(event);
			}
		}

		for (oxyU8 i = MouseButton{}; i < MouseButton_Count; ++i)
		{
			const auto isDown = IsMouseButtonDown(static_cast<MouseButton>(i));
			const auto wasDown =
				WasMouseButtonDown(static_cast<MouseButton>(i));
			if (isDown != wasDown)
			{
				MouseButtonStateChangedEvent event{};
				event.m_button = static_cast<MouseButton>(i);
				event.m_isDown = isDown;
				em.QueueEvent<MouseButtonStateChangedEvent>(event);
			}
		}

		{
			if (m_state.m_mouse.m_x != m_lastUpdateState.m_mouse.m_x ||
				m_state.m_mouse.m_y != m_lastUpdateState.m_mouse.m_y)
			{
				MouseMovedEvent event{};
				event.m_x = static_cast<oxyS32>(m_state.m_mouse.m_x);
				event.m_y = static_cast<oxyS32>(m_state.m_mouse.m_y);
				event.m_prevX =
					static_cast<oxyS32>(m_lastUpdateState.m_mouse.m_x);
				event.m_prevY =
					static_cast<oxyS32>(m_lastUpdateState.m_mouse.m_y);
				event.m_dx =
					m_state.m_mouse.m_x - m_lastUpdateState.m_mouse.m_x;
				event.m_dy =
					m_state.m_mouse.m_y - m_lastUpdateState.m_mouse.m_y;
				em.QueueEvent<MouseMovedEvent>(event);
			}
		}

		{
			for (auto i = 0; i < OXYGENMAXCONTROLLERS; ++i)
			{
				const auto isConnected = IsControllerConnected(i);
				const auto wasConnected =
					m_lastUpdateState.m_controllers[i].m_connected;
				if (isConnected != wasConnected)
				{
					ControllerConnectionStateChangedEvent event{};
					event.m_controllerIndex = i;
					event.m_isConnected = isConnected;
					em.QueueEvent<ControllerConnectionStateChangedEvent>(event);
				}

				for (oxyU8 j = ControllerAxis{}; j < ControllerAxis_Count; ++j)
				{
					const auto value = GetControllerAxisValue(i, static_cast<ControllerAxis>(j));
					const auto prevValue =
						m_lastUpdateState.m_controllers[i].m_axisValues[j];
					if (value != prevValue)
					{
						ControllerAxisValueChangedEvent event{};
						event.m_controllerIndex = i;
						event.m_axis = static_cast<ControllerAxis>(j);
						event.m_value = value;
						em.QueueEvent<ControllerAxisValueChangedEvent>(event);
					}
				}

				for (oxyU8 j = ControllerButton{}; j < ControllerButton_Count;
					++j)
				{
					const auto isDown =
						IsControllerButtonDown(i, static_cast<ControllerButton>(j));
					const auto wasDown = WasControllerButtonDown(
						i, static_cast<ControllerButton>(j));
					if (isDown != wasDown)
					{
						ControllerButtonStateChangedEvent event{};
						event.m_controllerIndex = i;
						event.m_button = static_cast<ControllerButton>(j);
						event.m_isDown = isDown;
						em.QueueEvent<ControllerButtonStateChangedEvent>(event);
					}
				}
			}
		}
	}
	auto InputManager::IsKeyDown(KeyboardButton button) const -> oxyBool
	{
		return m_state.m_keyboard.m_keys[button];
	}
	auto InputManager::WasKeyDown(KeyboardButton button) const -> oxyBool
	{
		return m_lastUpdateState.m_keyboard.m_keys[button];
	}
	auto InputManager::IsMouseButtonDown(MouseButton button) const -> oxyBool
	{
		return m_state.m_mouse.m_buttons[button];
	}
	auto InputManager::WasMouseButtonDown(MouseButton button) const -> oxyBool
	{
		return m_lastUpdateState.m_mouse.m_buttons[button];
	}
	auto InputManager::GetMousePosition(oxyS32& x, oxyS32& y) const -> void
	{
		x = static_cast<oxyS32>(m_state.m_mouse.m_x);
		y = static_cast<oxyS32>(m_state.m_mouse.m_y);
	}
	auto InputManager::GetMouseDelta(oxyF32& x, oxyF32& y) const -> void
	{
		x = m_state.m_mouse.m_x - m_lastUpdateState.m_mouse.m_x;
		y = m_state.m_mouse.m_y - m_lastUpdateState.m_mouse.m_y;
	}
	auto InputManager::IsControllerConnected(oxyS32 index) const -> oxyBool
	{
		return m_state.m_controllers[index].m_connected;
	}
	auto InputManager::GetControllerAxisValue(oxyS32 index,
											  ControllerAxis axis) const
		-> oxyF32
	{
		return m_state.m_controllers[index].m_axisValues[axis];
	}
	auto InputManager::IsControllerButtonDown(oxyS32 index,
											  ControllerButton button) const
		-> oxyBool
	{
		return m_state.m_controllers[index].m_buttonValues[button];
	}
	auto InputManager::WasControllerButtonDown(oxyS32 index,
											   ControllerButton button) const
		-> oxyBool
	{
		return m_lastUpdateState.m_controllers[index].m_buttonValues[button];
	}
}; // namespace oxygen