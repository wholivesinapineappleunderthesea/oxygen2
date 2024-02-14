#pragma once

#include "RenderContext/RenderContext.h"

namespace oxygen
{
	struct GfxRenderer : SingletonBase<GfxRenderer>
	{
		GfxRenderer();

		
		auto Render() -> void;

		oxyU16 m_width{};
		oxyU16 m_height{};
		oxyF32 m_aspectRatio{};

		// Vertex Shader: Default3P3N2UVUntexturedUVColor
		// Pixel Shader: Default3P3N2UVUntexturedUVColor
		// Input: float[3] position, float[3] normal, float[2] uv
		// StencilReadMask: 0xff
		// StencilWriteMask: 0xff
		// StencilPassOp: Keep
		// StencilFailOp: Keep
		// StencilDepthFailOp: Keep
		// StencilTest: Always
		// DepthWrite: Write
		// DepthTest: Less
		// Cull: CW
		// Fill: Solid
		// Blend: Additive
		std::shared_ptr<IPipelineState> m_psDefault3P3N2UVUntexturedUVColor;
		std::shared_ptr<IUniformBuffer> m_ubDefault3P3N2UVUntexturedUVColor;

		std::shared_ptr<IIndexBuffer> m_testib{};
		std::shared_ptr<IVertexBuffer> m_testvb{};
	};
}; // namespace oxygen