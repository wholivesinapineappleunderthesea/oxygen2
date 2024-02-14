#include <cstdint>

using oxyU8 = std::uint8_t;
using oxyU16 = std::uint16_t;
using oxyU32 = std::uint32_t;
using oxyU64 = std::uint64_t;
using oxyS8 = std::int8_t;
using oxyS16 = std::int16_t;
using oxyS32 = std::int32_t;
using oxyS64 = std::int64_t;

using oxyF32 = float;
using oxyF64 = double;

using oxyBool = bool;

using oxyChar = char;
using oxyWChar = wchar_t;

using oxySize = size_t;
using oxySSize = ptrdiff_t;

using oxyObjectID = oxyU64;

#include "Math/Defs.h"

namespace oxygen
{
	/**
	 * @brief A non-copyable type to be inherited from. Expresses clearly that a
	 * type cannot be copied.
	 *
	 */
	struct NonCopyable
	{
		NonCopyable() = default;
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;
	};

	struct GfxPlatformResourceHandle
	{
		static inline constexpr oxyU16 k_invalidHandle =
			~static_cast<oxyU16>(0U);
		oxyU16 m_handle{k_invalidHandle};
		using DestroyerFn_t = void (*)(oxyU16);
		DestroyerFn_t m_destroyer{};

		~GfxPlatformResourceHandle()
		{
			if (m_handle != k_invalidHandle && m_destroyer)
			{
				m_destroyer(m_handle);
			}
		}
		auto IsValid() const -> oxyBool
		{
			return m_handle != ~0U;
		}
	};

	/**
	 * @brief Priority effects order of event dispatch. Low priority events are
	 * dispatched last.
	 */
	enum EventPriority : oxyU8
	{
		EventPriority_Low,
		EventPriority_Medium,
		EventPriority_High,
		EventPriority_Count
	};

	/**
	 * @brief Event type enum. Used to identify the type of an event.
	 *
	 */
	enum EventType : oxyU16
	{
		EventType_Invalid,

		EventType_KeyboardButtonStateChangedEvent,
		EventType_MouseButtonStateChangedEvent,
		EventType_MouseMovedEvent,
		EventType_ControllerConnectionStateChangedEvent,
		EventType_ControllerAxisValueChangedEvent,
		EventType_ControllerButtonStateChangedEvent,

		EventType_SceneChangedEvent,

		EventType_Count
	};

	/**
	 * @brief Enum of controller buttons.
	 */
	enum ControllerButton : oxyU8
	{
		ControllerButton_LeftThumb,
		ControllerButton_RightThumb,
		ControllerButton_LeftShoulder,
		ControllerButton_RightShoulder,
		ControllerButton_A,
		ControllerButton_Cross = ControllerButton_A,
		ControllerButton_B,
		ControllerButton_Circle = ControllerButton_B,
		ControllerButton_X,
		ControllerButton_Square = ControllerButton_X,
		ControllerButton_Y,
		ControllerButton_Triangle = ControllerButton_Y,
		ControllerButton_Start,
		ControllerButton_Select = ControllerButton_Start,
		ControllerButton_Back,
		ControllerButton_Share = ControllerButton_Back,
		ControllerButton_DpadUp,
		ControllerButton_DpadDown,
		ControllerButton_DpadLeft,
		ControllerButton_DpadRight,
		ControllerButton_Count
	};

	/**
	 * @brief Enum of controller axes.
	 */
	enum ControllerAxis : oxyU8
	{
		ControllerAxis_LeftThumbX,
		ControllerAxis_LeftThumbY,
		ControllerAxis_RightThumbX,
		ControllerAxis_RightThumbY,
		ControllerAxis_LeftTrigger,
		ControllerAxis_RightTrigger,
		ControllerAxis_Count
	};

	/**
	 * @brief Enum of mouse buttons.
	 */
	enum MouseButton : oxyU8
	{
		MouseButton_Left,
		MouseButton_Right,
		MouseButton_Middle,
		MouseButton_X1,
		MouseButton_X2,
		MouseButton_Count
	};

	/**
	 * @brief Enum of keyboard buttons.
	 */
	enum KeyboardButton : oxyU8
	{
		// A-Z
		KeyboardButton_A,
		KeyboardButton_B,
		KeyboardButton_C,
		KeyboardButton_D,
		KeyboardButton_E,
		KeyboardButton_F,
		KeyboardButton_G,
		KeyboardButton_H,
		KeyboardButton_I,
		KeyboardButton_J,
		KeyboardButton_K,
		KeyboardButton_L,
		KeyboardButton_M,
		KeyboardButton_N,
		KeyboardButton_O,
		KeyboardButton_P,
		KeyboardButton_Q,
		KeyboardButton_R,
		KeyboardButton_S,
		KeyboardButton_T,
		KeyboardButton_U,
		KeyboardButton_V,
		KeyboardButton_W,
		KeyboardButton_X,
		KeyboardButton_Y,
		KeyboardButton_Z,

		// 0-9
		KeyboardButton_0,
		KeyboardButton_1,
		KeyboardButton_2,
		KeyboardButton_3,
		KeyboardButton_4,
		KeyboardButton_5,
		KeyboardButton_6,
		KeyboardButton_7,
		KeyboardButton_8,
		KeyboardButton_9,

		// F1-F24
		KeyboardButton_F1,
		KeyboardButton_F2,
		KeyboardButton_F3,
		KeyboardButton_F4,
		KeyboardButton_F5,
		KeyboardButton_F6,
		KeyboardButton_F7,
		KeyboardButton_F8,
		KeyboardButton_F9,
		KeyboardButton_F10,
		KeyboardButton_F11,
		KeyboardButton_F12,
		KeyboardButton_F13,
		KeyboardButton_F14,
		KeyboardButton_F15,
		KeyboardButton_F16,
		KeyboardButton_F17,
		KeyboardButton_F18,
		KeyboardButton_F19,
		KeyboardButton_F20,
		KeyboardButton_F21,
		KeyboardButton_F22,
		KeyboardButton_F23,
		KeyboardButton_F24,

		// Numpad 0-9
		KeyboardButton_NumPad0,
		KeyboardButton_NumPad1,
		KeyboardButton_NumPad2,
		KeyboardButton_NumPad3,
		KeyboardButton_NumPad4,
		KeyboardButton_NumPad5,
		KeyboardButton_NumPad6,
		KeyboardButton_NumPad7,
		KeyboardButton_NumPad8,
		KeyboardButton_NumPad9,

		// Numpad etc
		KeyboardButton_NumPadDecimal,
		KeyboardButton_NumPadEnter,
		KeyboardButton_NumPadAdd,
		KeyboardButton_NumPadSubtract,
		KeyboardButton_NumPadMultiply,
		KeyboardButton_NumPadDivide,
		KeyboardButton_NumPadLock,

		// Arrow keys
		KeyboardButton_Left,
		KeyboardButton_Right,
		KeyboardButton_Up,
		KeyboardButton_Down,

		// Home/End, Page Up/Down, Insert/Delete
		KeyboardButton_Home,
		KeyboardButton_End,
		KeyboardButton_PageUp,
		KeyboardButton_PageDown,
		KeyboardButton_Insert,
		KeyboardButton_Delete,

		// Pause/Break, Print Screen, Scroll Lock
		KeyboardButton_Pause,
		KeyboardButton_PrintScreen,
		KeyboardButton_ScrollLock,

		// Escape, Backtick, Tab, Caps Lock, Left Shift, Left Control, Left
		// Windows, Left Alt
		KeyboardButton_Escape,
		KeyboardButton_Backtick,
		KeyboardButton_Tab,
		KeyboardButton_CapsLock,
		KeyboardButton_LeftShift,
		KeyboardButton_LeftControl,
		KeyboardButton_LeftWindows,
		KeyboardButton_LeftAlt,

		// Space
		KeyboardButton_Space,

		// Right Alt, Right Function, Right Menu, Right Control, Right Shift,
		// Enter, Backspace
		KeyboardButton_RightAlt,
		KeyboardButton_RightFunction,
		KeyboardButton_RightMenu,
		KeyboardButton_RightControl,
		KeyboardButton_RightShift,
		KeyboardButton_Enter,
		KeyboardButton_Backspace,

		// Comma, Period, Slash, Semicolon, Apostrophe, Left Bracket, Right
		// Bracket, Backslash, Hyphen, Equals
		KeyboardButton_Comma,
		KeyboardButton_Period,
		KeyboardButton_Slash,
		KeyboardButton_Semicolon,
		KeyboardButton_Apostrophe,
		KeyboardButton_LeftBracket,
		KeyboardButton_RightBracket,
		KeyboardButton_Backslash,
		KeyboardButton_Hyphen,
		KeyboardButton_Equals,

		KeyboardButton_Count
	};

#define OXYGENMAXCONTROLLERS 4
#define OXYGENMINTHUMBVALUE -1.0f
#define OXYGENMAXTHUMBVALUE 1.0f
#define OXYGENMINTRIGGERVALUE 0.0f
#define OXYGENMAXTRIGGERVALUE 1.0f

	/**
	 * @brief Controller state.
	 */
	struct ControllerInputState
	{
		oxyBool m_connected{};
		oxyF32 m_axisValues[ControllerAxis_Count]{};
		oxyU8 m_buttonValues[ControllerButton_Count]{};
	};

	/**
	 * @brief Mouse state.
	 */
	struct MouseInputState
	{
		oxyF32 m_x{};
		oxyF32 m_y{};
		oxyU8 m_buttons[MouseButton_Count]{};
	};

	/**
	 * @brief Keyboard state.
	 */
	struct KeyboardInputState
	{
		oxyU8 m_keys[KeyboardButton_Count]{};
	};

	/**
	 * @brief Graphics formats.
	 */
	enum GfxFormat : oxyU8
	{
		GfxFormat_Invalid = 0,
		GfxFormat_BC1,
		GfxFormat_BC2,
		GfxFormat_BC3,
		GfxFormat_BC4,
		GfxFormat_BC5,
		GfxFormat_BC7,

		GfxFormat_R1,
		GfxFormat_A8,
		GfxFormat_R8,
		GfxFormat_R8U,
		GfxFormat_R8S,
		GfxFormat_R16,
		GfxFormat_R16U,
		GfxFormat_R16F,
		GfxFormat_R16S,
		GfxFormat_R32U,
		GfxFormat_R32F,
		GfxFormat_R32S,
		GfxFormat_RG8,
		GfxFormat_RG8U,
		GfxFormat_RG8S,
		GfxFormat_RG16,
		GfxFormat_RG16U,
		GfxFormat_RG16F,
		GfxFormat_RG16S,
		GfxFormat_RG32U,
		GfxFormat_RG32F,
		GfxFormat_RG32S,
		GfxFormat_RGB8,
		GfxFormat_RGB8U,
		GfxFormat_RGB8S,
		GfxFormat_RGB16,
		GfxFormat_RGB16U,
		GfxFormat_RGB16F,
		GfxFormat_RGB16S,
		GfxFormat_RGB32U,
		GfxFormat_RGB32F,
		GfxFormat_RGB32S,
		GfxFormat_BGRA8,
		GfxFormat_RGBA8,
		GfxFormat_RGBA8U,
		GfxFormat_RGBA8S,
		GfxFormat_RGBA16,
		GfxFormat_RGBA16U,
		GfxFormat_RGBA16F,
		GfxFormat_RGBA16S,
		GfxFormat_RGBA32U,
		GfxFormat_RGBA32F,
		GfxFormat_RGBA32S,

		GfxFormat_Depth16,
		GfxFormat_Depth24,
		GfxFormat_Depth32,
		GfxFormat_Depth16F,
		GfxFormat_Depth24F,
		GfxFormat_Depth32F,
		GfxFormat_Depth24Stencil8,
		GfxFormat_Depth32FStencil8,
		GfxFormat_Count,
	};

	enum GfxVertexElementSemantic : oxyU8
	{
		GfxVertexElementSemantic_Invalid = 0,
		GfxVertexElementSemantic_Position,
		GfxVertexElementSemantic_Normal,
		GfxVertexElementSemantic_TexCoord,
		GfxVertexElementSemantic_Count,
	};

	/**
	 * @brief Vertex element types.
	 */
	struct GfxVertexElement
	{
		oxyU16 m_offset{};
		GfxFormat m_format{};
		GfxVertexElementSemantic m_semantic{};
		oxyU8 m_semanticIndex{};

		static inline constexpr auto k_maxElements{16};
	};

	/**
	 * @brief Shader types.
	 */
	enum GfxShaderType : oxyU8
	{
		GfxShaderType_Geometry,
		GfxShaderType_Vertex,
		GfxShaderType_Pixel,
		GfxShaderType_Compute,
		GfxShaderType_Count,
	};

	/**
	 * @brief Fill types.
	 */
	enum GfxFill : oxyU8
	{
		GfxFill_Solid,
		GfxFill_Wireframe,
		GfxFill_Count,
	};

	/**
	 * @brief Cull types.
	 */
	enum GfxCull : oxyU8
	{
		GfxCull_None,
		GfxCull_CW,
		GfxCull_CCW,
		GfxCull_Count,
	};

	/**
	 * @brief Blend types.
	 */
	enum GfxBlend : oxyU8
	{
		GfxBlend_None,
		GfxBlend_Additive,
		GfxBlend_Subtract,
		GfxBlend_Count,
	};

	/**
	 * @brief Depth test types.
	 */
	enum GfxDepthTest : oxyU8
	{
		GfxDepthTest_None,
		GfxDepthTest_Less,
		GfxDepthTest_LessEqual,
		GfxDepthTest_Equal,
		GfxDepthTest_GreaterEqual,
		GfxDepthTest_Greater,
		GfxDepthTest_NotEqual,
		GfxDepthTest_Always,
		GfxDepthTest_Count,
	};

	/**
	 * @brief Depth write types.
	 */
	enum GfxDepthWrite : oxyU8
	{
		GfxDepthWrite_None,
		GfxDepthWrite_Write,
		GfxDepthWrite_Count,
	};

	/**
	 * @brief Stencil test types.
	 */
	enum GfxStencilTest : oxyU8
	{
		GfxStencilTest_None,
		GfxStencilTest_Less,
		GfxStencilTest_LessEqual,
		GfxStencilTest_Equal,
		GfxStencilTest_GreaterEqual,
		GfxStencilTest_Greater,
		GfxStencilTest_NotEqual,
		GfxStencilTest_Always,
		GfxStencilTest_Count,
	};

	/**
	 * @brief Stencil operation types.
	 */
	enum GfxStencilOp : oxyU8
	{
		GfxStencilOp_Keep,
		GfxStencilOp_Zero,
		GfxStencilOp_Replace,
		GfxStencilOp_Increment,
		GfxStencilOp_IncrementWrap,
		GfxStencilOp_Decrement,
		GfxStencilOp_DecrementWrap,
		GfxStencilOp_Invert,
		GfxStencilOp_Count,
	};

	/**
	 * @brief Hardcoded objects.
	 */
	enum HardcodedObjectIDs : oxyObjectID
	{
		HardcodedObjectID_RangeMin = 0x40,
		HardcodedObjectID_Universe = 0x40,
		HardcodedObjectID_GameManager = 0x41,
		HardcodedObjectID_DefaultMaterial = 0x42,
		HardcodedObjectID_WhiteMaterial = HardcodedObjectID_DefaultMaterial,
		HardcodedObjectID_RedMaterial = 0x43,
		HardcodedObjectID_GreenMaterial = 0x44,
		HardcodedObjectID_BlueMaterial = 0x45,
		HardcodedObjectID_CubeMesh = 0x46,
		HardcodedObjectID_RangeMax = 0x7F,
	};
}; // namespace oxygen
