#pragma once

namespace oxygen
{
	struct IRenderContextResource : NonCopyable
	{
		virtual ~IRenderContextResource() = default;
	};
	struct IVertexBuffer : IRenderContextResource
	{
		oxySize m_bufferSize{};
		oxySize m_vertexSize{};
		oxySize m_vertexCount{};
	};
	struct IIndexBuffer : IRenderContextResource
	{
		oxySize m_bufferSize{};
		oxySize m_indexSize{};
		oxySize m_indexCount{};
	};
	struct ITexture2D : IRenderContextResource
	{
		oxyU16 m_width{};
		oxyU16 m_height{};
		oxyU8 m_mipLevels{};
		oxyU8 m_arraySize{};
		GfxFormat m_format{};
	};
	struct IPipelineState : IRenderContextResource
	{
		oxyU8 m_stencilReadMask{};
		oxyU8 m_stencilWriteMask{};
		GfxStencilOp m_stencilPassOp{};
		GfxStencilOp m_stencilFailOp{};
		GfxStencilOp m_stencilDepthFailOp{};
		GfxStencilTest m_stencilTest{};

		GfxDepthWrite m_depthWrite{};
		GfxDepthTest m_depthTest{};

		GfxCull m_cull{};
		GfxFill m_fill{};

		GfxBlend m_blend{};

		oxySize m_vertexSize{};
		oxySize m_elementCount{};
		std::array<GfxVertexElement, GfxVertexElement::k_maxElements>
			m_elements{};
	};
	struct IUniformBuffer : IRenderContextResource
	{
		oxyU16 m_size{};
		oxyU8 m_includeInGeometryShader : 1 {};
		oxyU8 m_includeInVertexShader : 1 {};
		oxyU8 m_includeInPixelShader : 1 {};
		oxyU8 m_includeInComputeShader : 1 {};
	};

	struct VertexBufferCreationParams
	{
		oxySize m_vertexCount{};
		std::span<const oxyU8> m_data{};
	};
	struct IndexBufferCreationParams
	{
		oxySize m_indexCount{};
		std::span<const oxyU8> m_data{};
	};
	struct TextureCreationParams
	{
		oxyU16 m_width{};
		oxyU16 m_height{};
		oxyU8 m_mipLevels{};
		oxyU8 m_arraySize{};
		GfxFormat m_format{};
		std::span<const oxyU8> m_data{};
	};
	struct PipelineCreationParams
	{
		std::span<const oxyU8> m_shaderCode[GfxShaderType_Count]{};
		std::span<const GfxVertexElement> m_inputElements{};

		oxyU8 m_stencilReadMask{};
		oxyU8 m_stencilWriteMask{};
		GfxStencilOp m_stencilPassOp{};
		GfxStencilOp m_stencilFailOp{};
		GfxStencilOp m_stencilDepthFailOp{};
		GfxStencilTest m_stencilTest{};

		GfxDepthWrite m_depthWrite{};
		GfxDepthTest m_depthTest{};

		GfxCull m_cull{};
		GfxFill m_fill{};

		GfxBlend m_blend{};
	};
	struct UniformBufferCreationParams
	{
		oxyU16 m_size{};
		oxyU8 m_includeInGeometryShader : 1 {};
		oxyU8 m_includeInVertexShader : 1 {};
		oxyU8 m_includeInPixelShader : 1{};
		oxyU8 m_includeInComputeShader : 1{};
	};

	struct IRenderContext : NonCopyable
	{
		virtual ~IRenderContext() = default;
		virtual auto Resize(oxyU16 w, oxyU16 h, oxyBool isMinimized)
			-> void = 0;
		virtual auto BeginFrame() -> void = 0;
		virtual auto EndFrame() -> void = 0;

		virtual auto BeginResourceCreation() -> void = 0;
		virtual auto EndResourceCreation() -> void = 0;

		virtual auto CreatePipelineState(const PipelineCreationParams& params)
			-> std::shared_ptr<IPipelineState> = 0;
		virtual auto CreateTexture2D(const TextureCreationParams& params)
			-> std::shared_ptr<ITexture2D> = 0;
		virtual auto CreateIndexBuffer(const IndexBufferCreationParams& params)
			-> std::shared_ptr<IIndexBuffer> = 0;
		virtual auto
		CreateVertexBuffer(const VertexBufferCreationParams& params)
			-> std::shared_ptr<IVertexBuffer> = 0;
		virtual auto
		CreateUniformBuffer(const IPipelineState& pipeline,
							const UniformBufferCreationParams& params)
			-> std::shared_ptr<IUniformBuffer> = 0;

		virtual auto WriteUniformBuffer(const IUniformBuffer& buffer,
										const void* data, oxySize size)
			-> void = 0;

		virtual auto SetIndexBuffer(const IIndexBuffer& buffer) -> void = 0;
		virtual auto SetVertexBuffer(const IVertexBuffer& buffer) -> void = 0;
		virtual auto SetPipelineState(const IPipelineState& pipeline)
			-> void = 0;
		virtual auto SetUniformBuffer(const IUniformBuffer& buffer, oxyU8 slot) -> void = 0;
		virtual auto BindTexture2D(const ITexture2D& texture, oxyU8 slot)
			-> void = 0;

		virtual auto DrawIndexed(oxySize indexCount, oxySize indexOffset,
								 oxySize vertexOffset) -> void = 0;

		oxyU16 m_width{};
		oxyU16 m_height{};
		oxyBool m_isMinimized{};
	};

	auto CreateRenderContext(void* platformData)
		-> std::unique_ptr<IRenderContext>;
}; // namespace oxygen