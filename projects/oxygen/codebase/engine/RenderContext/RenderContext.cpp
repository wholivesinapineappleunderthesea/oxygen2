#include "OxygenPCH.h"
#include "RenderContext.h"
#include "Platform/Platform.h"
#ifdef OXYWIN32
#include "DX11/DX11RenderContext.h"
#endif

namespace oxygen
{
	auto CreateRenderContext(void* platformData)
		-> std::unique_ptr<IRenderContext>
	{
#ifdef OXYWIN32
		auto dx11 = CreateDX11RenderContext(static_cast<HWND>(platformData));
		if (dx11)
			return std::unique_ptr<IRenderContext>{dx11};
#endif
		return nullptr;
	}
} // namespace oxygen