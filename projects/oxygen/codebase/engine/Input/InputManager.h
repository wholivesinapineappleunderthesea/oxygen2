#pragma once

#include "Singleton/Singleton.h"

namespace oxygen
{
	/**
	 * @brief Singleton class that operates the input interface. Input state
	 * should be accessed during update calls and event callbacks.
	 */
	struct InputManager : SingletonBase<InputManager>
	{
		auto BeginUpdate(oxyF32 deltaTimeSeconds) -> void;
		auto UpdateController(oxyS32 index, const ControllerInputState& input)
			-> void;
		auto UpdateMouse(const MouseInputState& input) -> void;
		auto UpdateKeyboard(const KeyboardInputState& input) -> void;
		auto EndUpdate() -> void;

		auto IsKeyDown(KeyboardButton button) const -> oxyBool;
		auto WasKeyDown(KeyboardButton button) const -> oxyBool;
		auto IsMouseButtonDown(MouseButton button) const -> oxyBool;
		auto WasMouseButtonDown(MouseButton button) const -> oxyBool;
		auto GetMousePosition(oxyS32& x, oxyS32& y) const -> void;
		auto GetMouseDelta(oxyF32& x, oxyF32& y) const -> void;
		auto IsControllerConnected(oxyS32 index) const -> oxyBool;
		auto GetControllerAxisValue(oxyS32 index, ControllerAxis axis) const
			-> oxyF32;
		auto IsControllerButtonDown(oxyS32 index, ControllerButton button) const
			-> oxyBool;
		auto WasControllerButtonDown(oxyS32 index,
									 ControllerButton button) const -> oxyBool;

	  private:
		struct InputState
		{
			ControllerInputState m_controllers[OXYGENMAXCONTROLLERS]{};
			MouseInputState m_mouse{};
			KeyboardInputState m_keyboard{};
		};

		InputState m_state{};
		InputState m_lastUpdateState{};
	};
}; // namespace oxygen