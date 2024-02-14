#include "OxygenPCH.h"
#ifdef OXYWIN32
#include "Platform/Platform.h"
#include "PlatformWindows.h"

#include "RenderContext/RenderContext.h"

#include "Singleton/OxygenSingletons.h"

namespace
{
	auto g_instance = HINSTANCE{};
	auto g_exeDirectory = std::string{};
	auto g_hwnd = HWND{};
	auto g_renderContext = std::unique_ptr<oxygen::IRenderContext>{};
	auto g_inWindowLoop = false;
	const auto g_windowClassName = L"OxyWND01";
	const auto g_windowTitle = L"ARI.EXE";
	auto g_windowRect = RECT{};

	auto g_keyboard = oxygen::KeyboardInputState{};
	auto g_mouse = oxygen::MouseInputState{};

	LRESULT CALLBACK OxygenWindowCallback(HWND hwnd, UINT msg, WPARAM wParam,
										  LPARAM lParam)
	{

#define TESTKEYBTN(bridgeEnum, winKey)                                         \
	if (wParam == winKey && msg == WM_KEYDOWN)                                 \
	{                                                                          \
		g_keyboard.m_keys[oxygen::bridgeEnum] = true;                          \
	}                                                                          \
	else if (wParam == winKey && msg == WM_KEYUP)                              \
	{                                                                          \
		g_keyboard.m_keys[oxygen::bridgeEnum] = false;                         \
	}
		TESTKEYBTN(KeyboardButton_A, 'A');
		TESTKEYBTN(KeyboardButton_B, 'B');
		TESTKEYBTN(KeyboardButton_C, 'C');
		TESTKEYBTN(KeyboardButton_D, 'D');
		TESTKEYBTN(KeyboardButton_E, 'E');
		TESTKEYBTN(KeyboardButton_F, 'F');
		TESTKEYBTN(KeyboardButton_G, 'G');
		TESTKEYBTN(KeyboardButton_H, 'H');
		TESTKEYBTN(KeyboardButton_I, 'I');
		TESTKEYBTN(KeyboardButton_J, 'J');
		TESTKEYBTN(KeyboardButton_K, 'K');
		TESTKEYBTN(KeyboardButton_L, 'L');
		TESTKEYBTN(KeyboardButton_M, 'M');
		TESTKEYBTN(KeyboardButton_N, 'N');
		TESTKEYBTN(KeyboardButton_O, 'O');
		TESTKEYBTN(KeyboardButton_P, 'P');
		TESTKEYBTN(KeyboardButton_Q, 'Q');
		TESTKEYBTN(KeyboardButton_R, 'R');
		TESTKEYBTN(KeyboardButton_S, 'S');
		TESTKEYBTN(KeyboardButton_T, 'T');
		TESTKEYBTN(KeyboardButton_U, 'U');
		TESTKEYBTN(KeyboardButton_V, 'V');
		TESTKEYBTN(KeyboardButton_W, 'W');
		TESTKEYBTN(KeyboardButton_X, 'X');
		TESTKEYBTN(KeyboardButton_Y, 'Y');
		TESTKEYBTN(KeyboardButton_Z, 'Z');
		TESTKEYBTN(KeyboardButton_0, '0');
		TESTKEYBTN(KeyboardButton_1, '1');
		TESTKEYBTN(KeyboardButton_2, '2');
		TESTKEYBTN(KeyboardButton_3, '3');
		TESTKEYBTN(KeyboardButton_4, '4');
		TESTKEYBTN(KeyboardButton_5, '5');
		TESTKEYBTN(KeyboardButton_6, '6');
		TESTKEYBTN(KeyboardButton_7, '7');
		TESTKEYBTN(KeyboardButton_8, '8');
		TESTKEYBTN(KeyboardButton_9, '9');
		TESTKEYBTN(KeyboardButton_F1, VK_F1);
		TESTKEYBTN(KeyboardButton_F2, VK_F2);
		TESTKEYBTN(KeyboardButton_F3, VK_F3);
		TESTKEYBTN(KeyboardButton_F4, VK_F4);
		TESTKEYBTN(KeyboardButton_F5, VK_F5);
		TESTKEYBTN(KeyboardButton_F6, VK_F6);
		TESTKEYBTN(KeyboardButton_F7, VK_F7);
		TESTKEYBTN(KeyboardButton_F8, VK_F8);
		TESTKEYBTN(KeyboardButton_F9, VK_F9);
		TESTKEYBTN(KeyboardButton_F10, VK_F10);
		TESTKEYBTN(KeyboardButton_F11, VK_F11);
		TESTKEYBTN(KeyboardButton_F12, VK_F12);
		TESTKEYBTN(KeyboardButton_F13, VK_F13);
		TESTKEYBTN(KeyboardButton_F14, VK_F14);
		TESTKEYBTN(KeyboardButton_F15, VK_F15);
		TESTKEYBTN(KeyboardButton_F16, VK_F16);
		TESTKEYBTN(KeyboardButton_F17, VK_F17);
		TESTKEYBTN(KeyboardButton_F18, VK_F18);
		TESTKEYBTN(KeyboardButton_F19, VK_F19);
		TESTKEYBTN(KeyboardButton_F20, VK_F20);
		TESTKEYBTN(KeyboardButton_F21, VK_F21);
		TESTKEYBTN(KeyboardButton_F22, VK_F22);
		TESTKEYBTN(KeyboardButton_F23, VK_F23);
		TESTKEYBTN(KeyboardButton_F24, VK_F24);
		TESTKEYBTN(KeyboardButton_NumPad0, VK_NUMPAD0);
		TESTKEYBTN(KeyboardButton_NumPad1, VK_NUMPAD1);
		TESTKEYBTN(KeyboardButton_NumPad2, VK_NUMPAD2);
		TESTKEYBTN(KeyboardButton_NumPad3, VK_NUMPAD3);
		TESTKEYBTN(KeyboardButton_NumPad4, VK_NUMPAD4);
		TESTKEYBTN(KeyboardButton_NumPad5, VK_NUMPAD5);
		TESTKEYBTN(KeyboardButton_NumPad6, VK_NUMPAD6);
		TESTKEYBTN(KeyboardButton_NumPad7, VK_NUMPAD7);
		TESTKEYBTN(KeyboardButton_NumPad8, VK_NUMPAD8);
		TESTKEYBTN(KeyboardButton_NumPad9, VK_NUMPAD9);
		TESTKEYBTN(KeyboardButton_NumPadDecimal, VK_DECIMAL);
		TESTKEYBTN(KeyboardButton_NumPadEnter, VK_RETURN);
		TESTKEYBTN(KeyboardButton_NumPadAdd, VK_ADD);
		TESTKEYBTN(KeyboardButton_NumPadSubtract, VK_SUBTRACT);
		TESTKEYBTN(KeyboardButton_NumPadMultiply, VK_MULTIPLY);
		TESTKEYBTN(KeyboardButton_NumPadDivide, VK_DIVIDE);
		TESTKEYBTN(KeyboardButton_NumPadLock, VK_NUMLOCK);
		TESTKEYBTN(KeyboardButton_Left, VK_LEFT);
		TESTKEYBTN(KeyboardButton_Right, VK_RIGHT);
		TESTKEYBTN(KeyboardButton_Up, VK_UP);
		TESTKEYBTN(KeyboardButton_Down, VK_DOWN);
		TESTKEYBTN(KeyboardButton_Home, VK_HOME);
		TESTKEYBTN(KeyboardButton_End, VK_END);
		TESTKEYBTN(KeyboardButton_PageUp, VK_PRIOR);
		TESTKEYBTN(KeyboardButton_PageDown, VK_NEXT);
		TESTKEYBTN(KeyboardButton_Insert, VK_INSERT);
		TESTKEYBTN(KeyboardButton_Delete, VK_DELETE);
		TESTKEYBTN(KeyboardButton_Pause, VK_PAUSE);
		TESTKEYBTN(KeyboardButton_PrintScreen, VK_SNAPSHOT);
		TESTKEYBTN(KeyboardButton_ScrollLock, VK_SCROLL);
		TESTKEYBTN(KeyboardButton_Escape, VK_ESCAPE);
		TESTKEYBTN(KeyboardButton_Backtick, VK_OEM_3);
		TESTKEYBTN(KeyboardButton_Tab, VK_TAB);
		TESTKEYBTN(KeyboardButton_CapsLock, VK_CAPITAL);
		TESTKEYBTN(KeyboardButton_LeftShift, VK_SHIFT);
		TESTKEYBTN(KeyboardButton_LeftControl, VK_CONTROL);
		TESTKEYBTN(KeyboardButton_LeftWindows, VK_LWIN);
		TESTKEYBTN(KeyboardButton_LeftAlt, VK_LMENU);
		TESTKEYBTN(KeyboardButton_Space, VK_SPACE);
		TESTKEYBTN(KeyboardButton_RightAlt, VK_RMENU);
		TESTKEYBTN(KeyboardButton_RightFunction, VK_RWIN);
		TESTKEYBTN(KeyboardButton_RightMenu, VK_APPS);
		TESTKEYBTN(KeyboardButton_RightControl, VK_RCONTROL);
		TESTKEYBTN(KeyboardButton_RightShift, VK_RSHIFT);
		TESTKEYBTN(KeyboardButton_Enter, VK_RETURN);
		TESTKEYBTN(KeyboardButton_Backspace, VK_BACK);
		TESTKEYBTN(KeyboardButton_Comma, VK_OEM_COMMA);
		TESTKEYBTN(KeyboardButton_Period, VK_OEM_PERIOD);
		TESTKEYBTN(KeyboardButton_Slash, VK_OEM_2);
		TESTKEYBTN(KeyboardButton_Semicolon, VK_OEM_1);
		TESTKEYBTN(KeyboardButton_Apostrophe, VK_OEM_7);
		TESTKEYBTN(KeyboardButton_LeftBracket, VK_OEM_4);
		TESTKEYBTN(KeyboardButton_RightBracket, VK_OEM_6);
		TESTKEYBTN(KeyboardButton_Backslash, VK_OEM_5);
		TESTKEYBTN(KeyboardButton_Hyphen, VK_OEM_MINUS);
		TESTKEYBTN(KeyboardButton_Equals, VK_OEM_PLUS);
#undef TESTKEYBTN

		switch (msg)
		{
		case WM_CREATE: {
			GetClientRect(hwnd, &g_windowRect);

			g_renderContext = oxygen::CreateRenderContext(hwnd);

			break;
		}
		case WM_SIZE: {
			if (GetClientRect(hwnd, &g_windowRect))
			{
				if (g_renderContext)
				{
					const auto isMinimized = wParam == SIZE_MINIMIZED;
					g_renderContext->Resize(
						g_windowRect.right - g_windowRect.left,
						g_windowRect.bottom - g_windowRect.top, isMinimized);
				}
			}
			break;
		}
		case WM_INPUT: {
			UINT dwSize = 40;
			static BYTE lpb[40];

			GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize,
							sizeof(RAWINPUTHEADER));

			RAWINPUT* raw = (RAWINPUT*)lpb;

			if (raw->header.dwType == RIM_TYPEMOUSE)
			{
				int xPosRelative = raw->data.mouse.lLastX;
				int yPosRelative = raw->data.mouse.lLastY;
				int wheelDelta = raw->data.mouse.usButtonFlags;
				bool leftButton =
					raw->data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN;
				bool rightButton =
					raw->data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN;
				bool middleButton =
					raw->data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN;
				bool x1Button =
					raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_4_DOWN;
				bool x2Button =
					raw->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_5_DOWN;
			}
			break;
		}
		case WM_CLOSE: {
			PostQuitMessage(0);
			break;
		}
		case WM_DESTROY: {
			oxygen::OxygenSingletons::Destruct();
			g_renderContext.reset();
			g_hwnd = nullptr;
			break;
		}
		}
		return DefWindowProcW(hwnd, msg, wParam, lParam);
	}
	auto OxygenCreateWindow() -> oxyBool
	{
		WNDCLASSEXW wc{};
		wc.cbSize = sizeof wc;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = OxygenWindowCallback;
		wc.hInstance = g_instance;
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground =
			nullptr; // reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = g_windowClassName;
		wc.hIconSm = nullptr;
		if (!RegisterClassExW(&wc))
			return false;

		g_hwnd = CreateWindowExW(0, g_windowClassName, g_windowTitle,
								 WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
								 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
								 nullptr, nullptr, g_instance, nullptr);
		if (!g_hwnd)
			return false;

		ShowWindow(g_hwnd, SW_SHOW);
		UpdateWindow(g_hwnd);

		GetClientRect(g_hwnd, &g_windowRect);

		// Register for raw input
		RAWINPUTDEVICE rid[1];
		rid[0].usUsagePage = 0x01;
		rid[0].usUsage = 0x02;
		rid[0].dwFlags = 0;
		rid[0].hwndTarget = g_hwnd;
		if (!RegisterRawInputDevices(rid, 1, sizeof(rid[0])))
		{
			DestroyWindow(g_hwnd);
			g_hwnd = nullptr;
			return false;
		}

		return true;
	}
	auto OxygenProcessMessages() -> oxyBool
	{
		oxyBool quit{};
		MSG msg{};
		while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				quit = true;
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		return !quit;
	}
	auto OxygenDestroyWindow() -> void
	{
		if (g_hwnd)
			DestroyWindow(g_hwnd);
		g_hwnd = nullptr;
	}
}; // namespace

namespace oxygen
{
	auto Main(int argc, char* argv[]) -> int
	{
		g_instance = GetModuleHandleW(nullptr);

		g_exeDirectory.resize(MAX_PATH);
		GetModuleFileNameA(nullptr, g_exeDirectory.data(), MAX_PATH);
		g_exeDirectory =
			g_exeDirectory.substr(0, g_exeDirectory.find_last_of('\\'));
		std::replace(g_exeDirectory.begin(), g_exeDirectory.end(), '\\', '/');

		if (!OxygenCreateWindow())
			return 1;

		OxygenSingletons::Construct();

		oxygen::GameManager::GetInstance().StartGame();

		auto lastTime = GetHighPrecisionTime();
		while (OxygenProcessMessages())
		{
			g_inWindowLoop = true;
			const auto w = g_windowRect.right - g_windowRect.left;
			const auto h = g_windowRect.bottom - g_windowRect.top;
			// auto& gfx = GfxRenderer::GetInstance();
			// gfx.Render(w, h);
			const auto now = GetHighPrecisionTime();
			const auto dt = HighPrecisionTimeToSeconds(now - lastTime);
			lastTime = now;
			auto& im = InputManager::GetInstance();
			im.BeginUpdate(dt);
			im.UpdateKeyboard(g_keyboard);
			im.UpdateMouse(g_mouse);
			im.EndUpdate();

			if (g_renderContext)
			{
				g_renderContext->BeginFrame();
				auto& gfx = GfxRenderer::GetInstance();
				gfx.Render();

				g_renderContext->EndFrame();
			}
		}
		g_inWindowLoop = false;

		oxygen::GameManager::GetInstance().EndGame();

		OxygenSingletons::Destruct();

		OxygenDestroyWindow();
		return 0;
	}

	auto GetHighPrecisionTime() -> oxyU64
	{
		LONG high1;
		ULONG low;
		do
		{
			// STRICT! High1Time, LowPart, High2Time!
			high1 = USER_SHARED_DATA->InterruptTime.High1Time;
			low = USER_SHARED_DATA->InterruptTime.LowPart;
		} while (high1 != USER_SHARED_DATA->InterruptTime.High2Time);
		return (static_cast<oxyU64>(high1) << 32) + low;
	}
	auto HighPrecisionTimeToSeconds(oxyU64 time) -> oxyF64
	{
		return time / 10000000.0;
	}
	auto GetApplicationDirectory() -> std::string_view
	{
		return g_exeDirectory;
	}
	auto GetPlatformWindow() -> void*
	{
		return g_hwnd;
	}
	auto GetRenderContext() -> IRenderContext*
	{
		return g_renderContext.get();
	}
}; // namespace oxygen

#endif