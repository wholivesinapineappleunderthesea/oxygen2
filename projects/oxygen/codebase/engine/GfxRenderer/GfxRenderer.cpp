#include "OxygenPCH.h"
#include "GfxRenderer.h"

#include "DebugCamera/DebugCamera.h"
#include "Filesystem/Filesystem.h"
#include "Platform/Platform.h"

#include <d3dcompiler.h>

namespace oxygen
{
	GfxRenderer::GfxRenderer()
	{
		auto& fs = Filesystem::GetInstance();
		auto& renderContext = *GetRenderContext();
		renderContext.BeginResourceCreation();
		{
			const auto hlsl = fs.ReadFileFromExecutableDirectory(
				"shaders/Default3P3N2UVUntexturedUVColor.hlsl");

			GfxVertexElement elems[3]{};
			elems[0] = GfxVertexElement{0, GfxFormat_RGB32F,
										GfxVertexElementSemantic_Position, 0};
			elems[1] = GfxVertexElement{12, GfxFormat_RGB32F,
										GfxVertexElementSemantic_Normal, 0};
			elems[2] = GfxVertexElement{24, GfxFormat_RG32F,
										GfxVertexElementSemantic_TexCoord, 0};
			PipelineCreationParams params{};
			params.m_shaderCode[GfxShaderType_Vertex] = hlsl;
			params.m_shaderCode[GfxShaderType_Pixel] = hlsl;
			params.m_inputElements = elems;
			params.m_stencilReadMask = 0xff;
			params.m_stencilWriteMask = 0xff;
			params.m_stencilPassOp = GfxStencilOp_Keep;
			params.m_stencilFailOp = GfxStencilOp_Keep;
			params.m_stencilDepthFailOp = GfxStencilOp_Keep;
			params.m_stencilTest = GfxStencilTest_Always;
			params.m_depthWrite = GfxDepthWrite_Write;
			params.m_depthTest = GfxDepthTest_Always;
			params.m_cull = GfxCull_CW;
			params.m_fill = GfxFill_Solid;
			params.m_blend = GfxBlend_Additive;
			m_psDefault3P3N2UVUntexturedUVColor =
				renderContext.CreatePipelineState(params);
		}
		{
			UniformBufferCreationParams params{};
			params.m_size = (4 * 4 * 4) * 3;
			params.m_includeInGeometryShader = false;
			params.m_includeInVertexShader = true;
			params.m_includeInPixelShader = false;
			params.m_includeInComputeShader = false;
			m_ubDefault3P3N2UVUntexturedUVColor =
				renderContext.CreateUniformBuffer(
					*m_psDefault3P3N2UVUntexturedUVColor, params);
		}
		{
			const oxyU16 indices[3]{
				0,
				1,
				2,
			};
			IndexBufferCreationParams params{};
			params.m_data = {reinterpret_cast<const oxyU8*>(indices),
							 sizeof indices};
			params.m_indexCount = 3;
			m_testib = renderContext.CreateIndexBuffer(params);
		}
		{
			struct Vtx
			{
				oxyF32 m_pos[3];
				oxyF32 m_normal[3];
				oxyF32 m_uv[2];
			};
			Vtx vertices[3]{
				{{-1.0f, -1.0f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
				{{1.0f, -1.0f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
				{{0.0f, 1.0f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.5f, 1.0f}},
			};
			VertexBufferCreationParams params{};
			params.m_data = {reinterpret_cast<const oxyU8*>(vertices),
							 sizeof vertices};
			params.m_vertexCount = 3;
			m_testvb = renderContext.CreateVertexBuffer(params);
		}
		renderContext.EndResourceCreation();
	}
	auto GfxRenderer::Render() -> void
	{
		auto& renderContext = *GetRenderContext();

		m_width = renderContext.m_width;
		m_height = renderContext.m_height;
		m_aspectRatio = static_cast<oxyF32>(m_width) / m_height;

		//auto& dc = DebugCamera::GetInstance();
		//dc.ComputeMatrices();

		struct cb
		{
			oxyF32 m_model[4][4];
			oxyF32 m_view[4][4];
			oxyF32 m_proj[4][4];
		};
		cb cbData{};
		oxyMat4x4 model = oxyMat4x4::Identity();
		// model = Math::Scale(model, {2.5f, 2.5f, 2.5f});
		memcpy(cbData.m_model, &model[0][0], sizeof cbData.m_model);
		memcpy(cbData.m_view, &model[0][0], sizeof cbData.m_view);
		memcpy(cbData.m_proj, &model[0][0], sizeof cbData.m_proj);

		renderContext.WriteUniformBuffer(*m_ubDefault3P3N2UVUntexturedUVColor,
										 &cbData, sizeof cbData);

		renderContext.SetPipelineState(*m_psDefault3P3N2UVUntexturedUVColor);
		renderContext.SetIndexBuffer(*m_testib);
		renderContext.SetVertexBuffer(*m_testvb);
		renderContext.SetUniformBuffer(*m_ubDefault3P3N2UVUntexturedUVColor, 0);

		renderContext.DrawIndexed(3, 0, 0);
	}
}; // namespace oxygen