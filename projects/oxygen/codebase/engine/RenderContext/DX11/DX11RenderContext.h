#pragma once

#include "RenderContext/RenderContext.h"

#include <d3d11.h>
#include <dxgi1_3.h>
#include <wrl/client.h>

namespace oxygen
{
	struct DX11RenderContext : IRenderContext
	{
		~DX11RenderContext() override;

		auto Resize(oxyU16 w, oxyU16 h, oxyBool isMinimized) -> void override;
		auto BeginFrame() -> void override;
		auto EndFrame() -> void override;

		auto BeginResourceCreation() -> void override;
		auto EndResourceCreation() -> void override;

		auto CreatePipelineState(const PipelineCreationParams& params)
			-> std::shared_ptr<IPipelineState> override;
		auto CreateTexture2D(const TextureCreationParams& params)
			-> std::shared_ptr<ITexture2D> override;
		auto CreateIndexBuffer(const IndexBufferCreationParams& params)
			-> std::shared_ptr<IIndexBuffer> override;
		auto CreateVertexBuffer(const VertexBufferCreationParams& params)
			-> std::shared_ptr<IVertexBuffer> override;
		auto CreateUniformBuffer(const IPipelineState& pipeline,
								 const UniformBufferCreationParams& params)
			-> std::shared_ptr<IUniformBuffer> override;

		auto WriteUniformBuffer(const IUniformBuffer& buffer, const void* data,
								oxySize size) -> void override;

		auto SetIndexBuffer(const IIndexBuffer& buffer) -> void override;
		auto SetVertexBuffer(const IVertexBuffer& buffer) -> void override;
		auto SetPipelineState(const IPipelineState& pipeline) -> void override;
		auto SetUniformBuffer(const IUniformBuffer& buffer, oxyU8 slot)
			-> void override;
		auto BindTexture2D(const ITexture2D& texture, oxyU8 slot) -> void override;

		auto DrawIndexed(oxySize indexCount, oxySize indexOffset,
						 oxySize vertexOffset) -> void override;

		Microsoft::WRL::ComPtr<IDXGIAdapter> m_adapter{};
		Microsoft::WRL::ComPtr<ID3D11Device> m_device{};
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext{};
		Microsoft::WRL::ComPtr<IDXGISwapChain1> m_swapChain{};

		auto DestroySwapChainResources() -> void;
		auto CreateSwapChainResources() -> void;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_backBuffer{};
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView{};
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthStencilBuffer{};
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView{};
	};

	auto CreateDX11RenderContext(HWND wnd) -> DX11RenderContext*;
}; // namespace oxygen