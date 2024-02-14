#include "OxygenPCH.h"

#ifdef OXYWIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "DX11RenderContext.h"
#include <d3dcompiler.h>

namespace oxygen
{
	namespace
	{
		auto AlertFailed(const char* str, HRESULT hr = S_OK) -> void
		{
			char title[256] = "Error";
			if (hr != S_OK)
				sprintf_s(title, "Error: 0x%08X", hr);
			MessageBoxA(nullptr, str, title, MB_OK);
		}
		struct DX11RenderContextPipelineState : IPipelineState
		{
			Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader{};
			Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader{};
			Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader{};
			Microsoft::WRL::ComPtr<ID3D11ComputeShader> m_computeShader{};

			Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerState{};
			Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState{};
			Microsoft::WRL::ComPtr<ID3D11DepthStencilState>
				m_depthStencilState{};
			Microsoft::WRL::ComPtr<ID3D11InputLayout> m_layout{};
		};
		struct DX11Texture2D : ITexture2D
		{
			Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture{};
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_srv{};
		};
		struct DX11RenderContextIndexBuffer : IIndexBuffer
		{
			Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer{};
		};
		struct DX11RenderContextVertexBuffer : IVertexBuffer
		{
			Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer{};
		};
		struct DX11RenderContextUniformBuffer : IUniformBuffer
		{
			Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer{};
		};

		auto DX11RenderContextConvertGfxStencilOp(GfxStencilOp op,
												  D3D11_STENCIL_OP& outOp)
			-> oxyBool
		{
			switch (op)
			{
			case GfxStencilOp_Keep:
				outOp = D3D11_STENCIL_OP_KEEP;
				return true;
			case GfxStencilOp_Zero:
				outOp = D3D11_STENCIL_OP_ZERO;
				return true;
			case GfxStencilOp_Replace:
				outOp = D3D11_STENCIL_OP_REPLACE;
				return true;
			case GfxStencilOp_Increment:
				outOp = D3D11_STENCIL_OP_INCR;
				return true;
			case GfxStencilOp_IncrementWrap:
				outOp = D3D11_STENCIL_OP_INCR_SAT;
				return true;
			case GfxStencilOp_Decrement:
				outOp = D3D11_STENCIL_OP_DECR;
				return true;
			case GfxStencilOp_DecrementWrap:
				outOp = D3D11_STENCIL_OP_DECR_SAT;
				return true;
			case GfxStencilOp_Invert:
				outOp = D3D11_STENCIL_OP_INVERT;
				return true;
			}
			return false;
		}

		auto DX11RenderContextConvertGfxStencilTest(
			GfxStencilTest func, D3D11_COMPARISON_FUNC& outFunc) -> oxyBool
		{
			switch (func)
			{
			case GfxStencilTest_None:
				outFunc = D3D11_COMPARISON_NEVER;
				return true;
			case GfxStencilTest_Less:
				outFunc = D3D11_COMPARISON_LESS;
				return true;
			case GfxStencilTest_LessEqual:
				outFunc = D3D11_COMPARISON_LESS_EQUAL;
				return true;
			case GfxStencilTest_Equal:
				outFunc = D3D11_COMPARISON_EQUAL;
				return true;
			case GfxStencilTest_GreaterEqual:
				outFunc = D3D11_COMPARISON_GREATER_EQUAL;
				return true;
			case GfxStencilTest_Greater:
				outFunc = D3D11_COMPARISON_GREATER;
				return true;
			case GfxStencilTest_NotEqual:
				outFunc = D3D11_COMPARISON_NOT_EQUAL;
				return true;
			case GfxStencilTest_Always:
				outFunc = D3D11_COMPARISON_ALWAYS;
				return true;
			}
			return false;
		}

		auto DX11RenderContextConvertGfxFormat(GfxFormat format,
											   DXGI_FORMAT& outFormat)
			-> oxyBool
		{
			switch (format)
			{
#define CASEGFXFORMAT(x, y)                                                    \
	case GfxFormat_##x:                                                        \
		outFormat = DXGI_FORMAT_##y;                                           \
		return true;
				CASEGFXFORMAT(BC1, BC1_UNORM);
				CASEGFXFORMAT(BC2, BC2_UNORM);
				CASEGFXFORMAT(BC3, BC3_UNORM);
				CASEGFXFORMAT(BC4, BC4_UNORM);
				CASEGFXFORMAT(BC5, BC5_UNORM);
				CASEGFXFORMAT(BC7, BC7_UNORM);
				CASEGFXFORMAT(R1, R1_UNORM);
				CASEGFXFORMAT(A8, A8_UNORM);
				CASEGFXFORMAT(R8, R8_UNORM);
				CASEGFXFORMAT(R8U, R8_UINT);
				CASEGFXFORMAT(R8S, R8_SNORM);
				CASEGFXFORMAT(R16, R16_UNORM);
				CASEGFXFORMAT(R16U, R16_UINT);
				CASEGFXFORMAT(R16F, R16_FLOAT);
				CASEGFXFORMAT(R16S, R16_SNORM);
				CASEGFXFORMAT(R32U, R32_UINT);
				CASEGFXFORMAT(R32F, R32_FLOAT);
				CASEGFXFORMAT(R32S, R32_SINT);
				CASEGFXFORMAT(RG8, R8G8_UNORM);
				CASEGFXFORMAT(RG8U, R8G8_UINT);
				CASEGFXFORMAT(RG8S, R8G8_SNORM);
				CASEGFXFORMAT(RG16, R16G16_UNORM);
				CASEGFXFORMAT(RG16U, R16G16_UINT);
				CASEGFXFORMAT(RG16F, R16G16_FLOAT);
				CASEGFXFORMAT(RG16S, R16G16_SNORM);
				CASEGFXFORMAT(RG32U, R32G32_UINT);
				CASEGFXFORMAT(RG32F, R32G32_FLOAT);
				CASEGFXFORMAT(RG32S, R32G32_SINT);
				// CASEGFXFORMAT(RGB8, R8G8B8_UNORM);
				// CASEGFXFORMAT(RGB8U, R8G8B8_UINT);
				// CASEGFXFORMAT(RGB8S, R8G8B8_SNORM);
				// CASEGFXFORMAT(RGB16, R16G16B16_UNORM);
				// CASEGFXFORMAT(RGB16U, R16G16B16_UINT);
				// CASEGFXFORMAT(RGB16F, R16G16B16_FLOAT);
				// CASEGFXFORMAT(RGB16S, R16G16B16_SNORM);
				CASEGFXFORMAT(RGB32U, R32G32B32_UINT);
				CASEGFXFORMAT(RGB32F, R32G32B32_FLOAT);
				CASEGFXFORMAT(RGB32S, R32G32B32_SINT);
				CASEGFXFORMAT(RGBA8, R8G8B8A8_UNORM);
				CASEGFXFORMAT(RGBA8U, R8G8B8A8_UINT);
				CASEGFXFORMAT(RGBA8S, R8G8B8A8_SNORM);
				CASEGFXFORMAT(RGBA16, R16G16B16A16_UNORM);
				CASEGFXFORMAT(RGBA16U, R16G16B16A16_UINT);
				CASEGFXFORMAT(RGBA16F, R16G16B16A16_FLOAT);
				CASEGFXFORMAT(RGBA16S, R16G16B16A16_SNORM);
				CASEGFXFORMAT(RGBA32U, R32G32B32A32_UINT);
				CASEGFXFORMAT(RGBA32F, R32G32B32A32_FLOAT);
				CASEGFXFORMAT(RGBA32S, R32G32B32A32_SINT);
				CASEGFXFORMAT(Depth16, D16_UNORM);
				CASEGFXFORMAT(Depth32, D32_FLOAT);
				CASEGFXFORMAT(Depth24, D24_UNORM_S8_UINT); // this is odd
				CASEGFXFORMAT(Depth32F, D32_FLOAT);
				CASEGFXFORMAT(Depth24Stencil8, D24_UNORM_S8_UINT);
				CASEGFXFORMAT(Depth32FStencil8, D32_FLOAT_S8X24_UINT);
#undef CASEGFXFORMAT
			}
			return false;
		}
	}; // namespace

	auto CreateDX11RenderContext(HWND wnd) -> DX11RenderContext*
	{
		Microsoft::WRL::ComPtr<IDXGIFactory2> factory{};
		auto hr = CreateDXGIFactory2(
			0, __uuidof(IDXGIFactory2),
			reinterpret_cast<void**>(factory.ReleaseAndGetAddressOf()));
		if (FAILED(hr))
		{
			AlertFailed("Failed to create DXGI factory", hr);
			return nullptr;
		}

		std::vector<Microsoft::WRL::ComPtr<IDXGIAdapter>> adapters{};
		{
			Microsoft::WRL::ComPtr<IDXGIAdapter> adapter{};
			for (UINT i = 0;
				 factory->EnumAdapters(i, adapter.ReleaseAndGetAddressOf()) !=
				 DXGI_ERROR_NOT_FOUND;
				 ++i)
			{
				adapters.emplace_back(adapter);
				adapter = nullptr;
			}
		}

		if (!adapters.size())
		{
			AlertFailed("No DX11 adapters found");
			return nullptr;
		}

		Microsoft::WRL::ComPtr<ID3D11Device> device{};
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> context{};
		D3D_FEATURE_LEVEL featureLevel{};
		Microsoft::WRL::ComPtr<IDXGIAdapter> chosenAdapter{};
		for (auto& adapter : adapters)
		{
			hr = D3D11CreateDevice(
				adapter.Get(), D3D_DRIVER_TYPE_UNKNOWN, nullptr,
				D3D11_CREATE_DEVICE_BGRA_SUPPORT
#ifdef OXYDEBUG
					| D3D11_CREATE_DEVICE_DEBUG
#endif
				,
				nullptr, 0, D3D11_SDK_VERSION, device.GetAddressOf(),
				&featureLevel, context.GetAddressOf());
			if (SUCCEEDED(hr))
			{
				chosenAdapter = adapter;
				break;
			}
		}
		if (!device)
		{
			return nullptr;
		}
		if (!context)
		{
			return nullptr;
		}

		RECT clientRect{};
		GetClientRect(wnd, &clientRect);

		DXGI_SWAP_CHAIN_DESC swapChainDesc{};
		swapChainDesc.BufferDesc.Width = clientRect.right - clientRect.left;
		swapChainDesc.BufferDesc.Height = clientRect.bottom - clientRect.top;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering =
			DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = wnd;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain0{};
		hr = factory->CreateSwapChain(device.Get(), &swapChainDesc,
									  swapChain0.GetAddressOf());
		if (FAILED(hr))
		{
			AlertFailed("Failed to create swap chain", hr);
			return nullptr;
		}
		Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain1{};
		hr = swapChain0.As(&swapChain1);
		if (FAILED(hr))
		{
			AlertFailed("Failed to create swap chain", hr);
			return nullptr;
		}

		DX11RenderContext* ctx = new DX11RenderContext();
		ctx->m_width = swapChainDesc.BufferDesc.Width;
		ctx->m_height = swapChainDesc.BufferDesc.Height;
		ctx->m_isMinimized = false;
		ctx->m_adapter = chosenAdapter;
		ctx->m_device = device;
		ctx->m_deviceContext = context;
		ctx->m_swapChain = swapChain1;
		ctx->CreateSwapChainResources();
		return ctx;
	}
	DX11RenderContext::~DX11RenderContext()
	{
		if (m_swapChain)
			m_swapChain->SetFullscreenState(FALSE, 0);
	}
	auto DX11RenderContext::Resize(oxyU16 w, oxyU16 h, oxyBool minimized)
		-> void
	{
		m_width = w;
		m_height = h;
		m_deviceContext->Flush();
		DestroySwapChainResources();
		auto hr = m_swapChain->ResizeBuffers(0, w, h, DXGI_FORMAT_UNKNOWN, 0);
		if (FAILED(hr))
		{
			AlertFailed("Failed to resize swap chain buffers", hr);
		}
		CreateSwapChainResources();
	}
	auto DX11RenderContext::BeginFrame() -> void
	{
		D3D11_RECT scissorRect{};
		scissorRect.left = 0;
		scissorRect.top = 0;
		scissorRect.right = m_width;
		scissorRect.bottom = m_height;
		m_deviceContext->RSSetScissorRects(1, &scissorRect);

		D3D11_VIEWPORT vp{};
		vp.Width = static_cast<FLOAT>(m_width);
		vp.Height = static_cast<FLOAT>(m_height);
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_deviceContext->RSSetViewports(1, &vp);

		float color[4] = {0.0f, 0.0f, 0.0f, 0.0f};
		m_deviceContext->ClearRenderTargetView(m_renderTargetView.Get(), color);

		m_deviceContext->ClearDepthStencilView(
			m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
			1.0f, 0);

		m_deviceContext->OMSetRenderTargets(
			1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());
	}
	auto DX11RenderContext::EndFrame() -> void
	{
		auto hr = m_swapChain->Present(0, 0);
		if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
		{
			AlertFailed("Device removed or reset", hr);
		}
		else if (FAILED(hr))
		{
			AlertFailed("Failed to present", hr);
		}
	}
	auto DX11RenderContext::BeginResourceCreation() -> void
	{
	}
	auto DX11RenderContext::EndResourceCreation() -> void
	{
	}
	auto
	DX11RenderContext::CreatePipelineState(const PipelineCreationParams& params)
		-> std::shared_ptr<IPipelineState>
	{
		Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> geometryShader;
		Microsoft::WRL::ComPtr<ID3D11ComputeShader> computeShader;
		Microsoft::WRL::ComPtr<ID3DBlob> vsBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> psBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> gsBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> csBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

		if (params.m_shaderCode[GfxShaderType_Vertex].size())
		{
			auto hr = D3DCompile2(
				params.m_shaderCode[GfxShaderType_Vertex].data(),
				params.m_shaderCode[GfxShaderType_Vertex].size_bytes(), nullptr,
				nullptr, nullptr, "vs_main", "vs_5_0", 0, 0, 0, nullptr, 0,
				&vsBlob, errorBlob.ReleaseAndGetAddressOf());
			if (FAILED(hr))
			{
				std::string errorStr = "Failed to compile vertex shader";
				if (errorBlob)
					errorStr +=
						"\n" + std::string(reinterpret_cast<const char*>(
											   errorBlob->GetBufferPointer()),
										   errorBlob->GetBufferSize());
				AlertFailed(errorStr.c_str(), hr);
				return nullptr;
			}
			hr = m_device->CreateVertexShader(vsBlob->GetBufferPointer(),
											  vsBlob->GetBufferSize(), nullptr,
											  vertexShader.GetAddressOf());
			if (FAILED(hr))
			{
				AlertFailed("Failed to create vertex shader", hr);
				return nullptr;
			}
		}
		if (params.m_shaderCode[GfxShaderType_Pixel].size())
		{
			auto hr = D3DCompile2(
				params.m_shaderCode[GfxShaderType_Pixel].data(),
				params.m_shaderCode[GfxShaderType_Pixel].size_bytes(), nullptr,
				nullptr, nullptr, "ps_main", "ps_5_0", 0, 0, 0, nullptr, 0,
				&psBlob, errorBlob.ReleaseAndGetAddressOf());
			if (FAILED(hr))
			{
				std::string errorStr = "Failed to compile vertex shader";
				if (errorBlob)
					errorStr +=
						"\n" + std::string(reinterpret_cast<const char*>(
											   errorBlob->GetBufferPointer()),
										   errorBlob->GetBufferSize());
				AlertFailed(errorStr.c_str(), hr);
				return nullptr;
			}
			hr = m_device->CreatePixelShader(psBlob->GetBufferPointer(),
											 psBlob->GetBufferSize(), nullptr,
											 pixelShader.GetAddressOf());
			if (FAILED(hr))
			{
				AlertFailed("Failed to create pixel shader", hr);
				return nullptr;
			}
		}
		if (params.m_shaderCode[GfxShaderType_Geometry].size())
		{
			auto hr = D3DCompile2(
				params.m_shaderCode[GfxShaderType_Geometry].data(),
				params.m_shaderCode[GfxShaderType_Geometry].size_bytes(),
				nullptr, nullptr, nullptr, "gs_main", "gs_5_0", 0, 0, 0,
				nullptr, 0, &gsBlob, errorBlob.ReleaseAndGetAddressOf());
			if (FAILED(hr))
			{
				std::string errorStr = "Failed to compile vertex shader";
				if (errorBlob)
					errorStr +=
						"\n" + std::string(reinterpret_cast<const char*>(
											   errorBlob->GetBufferPointer()),
										   errorBlob->GetBufferSize());
				AlertFailed(errorStr.c_str(), hr);
				return nullptr;
			}
			hr = m_device->CreateGeometryShader(
				gsBlob->GetBufferPointer(), gsBlob->GetBufferSize(), nullptr,
				geometryShader.GetAddressOf());
			if (FAILED(hr))
			{
				AlertFailed("Failed to create geometry shader", hr);
				return nullptr;
			}
		}
		if (params.m_shaderCode[GfxShaderType_Compute].size())
		{
			auto hr = D3DCompile2(
				params.m_shaderCode[GfxShaderType_Compute].data(),
				params.m_shaderCode[GfxShaderType_Compute].size_bytes(),
				nullptr, nullptr, nullptr, "cs_main", "cs_5_0", 0, 0, 0,
				nullptr, 0, &csBlob, errorBlob.ReleaseAndGetAddressOf());
			if (FAILED(hr))
			{
				std::string errorStr = "Failed to compile vertex shader";
				if (errorBlob)
					errorStr +=
						"\n" + std::string(reinterpret_cast<const char*>(
											   errorBlob->GetBufferPointer()),
										   errorBlob->GetBufferSize());
				AlertFailed(errorStr.c_str(), hr);
				return nullptr;
			}
			hr = m_device->CreateComputeShader(
				params.m_shaderCode[GfxShaderType_Compute].data(),
				params.m_shaderCode[GfxShaderType_Compute].size_bytes(),
				nullptr, computeShader.GetAddressOf());
			if (FAILED(hr))
			{
				AlertFailed("Failed to create compute shader", hr);
				return nullptr;
			}
		}

		Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState;
		{
			D3D11_RASTERIZER_DESC desc{};
			desc.FillMode = params.m_fill == GfxFill_Solid
								? D3D11_FILL_SOLID
								: D3D11_FILL_WIREFRAME;
			desc.CullMode = params.m_cull == GfxCull_None ? D3D11_CULL_NONE
							: params.m_cull == GfxCull_CW ? D3D11_CULL_FRONT
														  : D3D11_CULL_BACK;
			desc.FrontCounterClockwise = FALSE;
			desc.DepthBias = 0;
			desc.DepthBiasClamp = 0.0f;
			desc.SlopeScaledDepthBias = 0.0f;
			desc.DepthClipEnable = TRUE;
			desc.ScissorEnable = TRUE;
			desc.MultisampleEnable = FALSE;
			desc.AntialiasedLineEnable = FALSE;
			auto hr = m_device->CreateRasterizerState(
				&desc, rasterizerState.GetAddressOf());
			if (FAILED(hr))
			{
				AlertFailed("Failed to create rasterizer state", hr);
				return nullptr;
			}
		}

		Microsoft::WRL::ComPtr<ID3D11BlendState> blendState;
		{
			D3D11_BLEND_DESC desc{};
			desc.AlphaToCoverageEnable = FALSE;
			desc.IndependentBlendEnable = FALSE;
			desc.RenderTarget[0].BlendEnable = params.m_blend != GfxBlend_None;
			desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			desc.RenderTarget[0].BlendOp = params.m_blend == GfxBlend_Additive
											   ? D3D11_BLEND_OP_ADD
											   : D3D11_BLEND_OP_SUBTRACT;
			desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			desc.RenderTarget[0].RenderTargetWriteMask =
				D3D11_COLOR_WRITE_ENABLE_ALL;
			auto hr =
				m_device->CreateBlendState(&desc, blendState.GetAddressOf());
			if (FAILED(hr))
			{
				AlertFailed("Failed to create blend state", hr);
				return nullptr;
			}
		}

		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> stencilDepth;
		{
			D3D11_DEPTH_STENCIL_DESC desc{};
			desc.DepthEnable = params.m_depthTest != GfxDepthTest_None;
			desc.DepthWriteMask = params.m_depthWrite == GfxDepthWrite_Write
									  ? D3D11_DEPTH_WRITE_MASK_ALL
									  : D3D11_DEPTH_WRITE_MASK_ZERO;
			desc.DepthFunc = D3D11_COMPARISON_LESS;

			desc.StencilEnable = params.m_stencilTest != GfxStencilTest_None;
			desc.StencilReadMask = params.m_stencilReadMask;
			desc.StencilWriteMask = params.m_stencilWriteMask;
			DX11RenderContextConvertGfxStencilTest(params.m_stencilTest,
												   desc.FrontFace.StencilFunc);
			DX11RenderContextConvertGfxStencilOp(params.m_stencilPassOp,
												 desc.FrontFace.StencilFailOp);
			DX11RenderContextConvertGfxStencilOp(params.m_stencilFailOp,
												 desc.FrontFace.StencilPassOp);
			DX11RenderContextConvertGfxStencilOp(
				params.m_stencilDepthFailOp, desc.FrontFace.StencilDepthFailOp);
			// ari: this is more complicated than I thought,
			// some more complicated rendering techniques might need
			// backface/frontface stencil separation
			desc.BackFace = desc.FrontFace;
			auto hr = m_device->CreateDepthStencilState(
				&desc, stencilDepth.GetAddressOf());
			if (FAILED(hr))
			{
				AlertFailed("Failed to create depth stencil state", hr);
				return nullptr;
			}
		}

		Microsoft::WRL::ComPtr<ID3D11InputLayout> layout{};
		if (vsBlob)
		{
			D3D11_INPUT_ELEMENT_DESC dxelem[GfxVertexElement::k_maxElements]{};
			for (oxyU32 i = 0; i < params.m_inputElements.size(); ++i)
			{
				auto& element = params.m_inputElements[i];
				const char* semanticName{};
				switch (element.m_semantic)
				{
				case GfxVertexElementSemantic_Position:
					semanticName = "POSITION";
					break;
				case GfxVertexElementSemantic_Normal:
					semanticName = "NORMAL";
					break;
				case GfxVertexElementSemantic_TexCoord:
					semanticName = "TEXCOORD";
					break;
				};
				if (!semanticName)
					break;
				dxelem[i].SemanticName = semanticName;
				dxelem[i].SemanticIndex = element.m_semanticIndex;
				dxelem[i].Format = DXGI_FORMAT_R32G32B32_FLOAT;
				DX11RenderContextConvertGfxFormat(element.m_format,
												  dxelem[i].Format);
				dxelem[i].InputSlot = 0;
				dxelem[i].AlignedByteOffset = element.m_offset;
				dxelem[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				dxelem[i].InstanceDataStepRate = 0;
			}
			auto hr = m_device->CreateInputLayout(
				dxelem, params.m_inputElements.size(),
				vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(),
				layout.GetAddressOf());
			if (FAILED(hr))
			{
				AlertFailed("Failed to create input layout", hr);
				return nullptr;
			}
		}

		auto state = std::make_shared<DX11RenderContextPipelineState>();
		state->m_vertexShader = std::move(vertexShader);
		state->m_pixelShader = std::move(pixelShader);
		state->m_geometryShader = std::move(geometryShader);
		state->m_computeShader = std::move(computeShader);
		state->m_rasterizerState = std::move(rasterizerState);
		state->m_blendState = std::move(blendState);
		state->m_depthStencilState = std::move(stencilDepth);
		state->m_layout = std::move(layout);
		state->m_stencilReadMask = params.m_stencilReadMask;
		state->m_stencilWriteMask = params.m_stencilWriteMask;
		state->m_stencilPassOp = params.m_stencilPassOp;
		state->m_stencilFailOp = params.m_stencilFailOp;
		state->m_stencilDepthFailOp = params.m_stencilDepthFailOp;
		state->m_stencilTest = params.m_stencilTest;
		state->m_depthWrite = params.m_depthWrite;
		state->m_depthTest = params.m_depthTest;
		state->m_fill = params.m_fill;
		state->m_cull = params.m_cull;
		state->m_blend = params.m_blend;
		return state;
	}
	auto DX11RenderContext::CreateTexture2D(const TextureCreationParams& params)
		-> std::shared_ptr<ITexture2D>
	{
		Microsoft::WRL::ComPtr<ID3D11Texture2D> texture{};
		D3D11_TEXTURE2D_DESC desc{};
		desc.Width = params.m_width;
		desc.Height = params.m_height;
		desc.MipLevels = params.m_mipLevels;
		desc.ArraySize = params.m_arraySize;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		DX11RenderContextConvertGfxFormat(params.m_format, desc.Format);
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		auto hr =
			m_device->CreateTexture2D(&desc, nullptr, texture.GetAddressOf());
		if (FAILED(hr))
		{
			AlertFailed("Failed to create texture2D", hr);
			return nullptr;
		}
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv{};
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
		srvDesc.Format = desc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = desc.MipLevels;
		hr = m_device->CreateShaderResourceView(texture.Get(), &srvDesc,
												srv.GetAddressOf());
		if (FAILED(hr))
		{
			AlertFailed("Failed to create shader resource view", hr);
			return nullptr;
		}
		auto tex = std::make_shared<DX11Texture2D>();
		tex->m_texture = std::move(texture);
		tex->m_srv = srv;
		return tex;
	}
	auto DX11RenderContext::CreateIndexBuffer(
		const IndexBufferCreationParams& params)
		-> std::shared_ptr<IIndexBuffer>
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer{};
		D3D11_BUFFER_DESC desc{};
		desc.ByteWidth = params.m_data.size_bytes();
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA data{};
		data.pSysMem = params.m_data.data();
		auto hr = m_device->CreateBuffer(&desc, &data, buffer.GetAddressOf());
		if (FAILED(hr))
		{
			AlertFailed("Failed to create index buffer", hr);
			return nullptr;
		}
		auto ib = std::make_shared<DX11RenderContextIndexBuffer>();
		ib->m_buffer = std::move(buffer);
		ib->m_indexCount = params.m_indexCount;
		ib->m_indexSize = params.m_data.size_bytes() / params.m_indexCount;
		ib->m_bufferSize = params.m_data.size_bytes();
		return ib;
	}
	auto DX11RenderContext::CreateVertexBuffer(
		const VertexBufferCreationParams& params)
		-> std::shared_ptr<IVertexBuffer>
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer{};
		D3D11_BUFFER_DESC desc{};
		desc.ByteWidth = params.m_data.size_bytes();
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA data{};
		data.pSysMem = params.m_data.data();
		auto hr = m_device->CreateBuffer(&desc, &data, buffer.GetAddressOf());
		if (FAILED(hr))
		{
			AlertFailed("Failed to create vertex buffer", hr);
			return nullptr;
		}
		auto vb = std::make_shared<DX11RenderContextVertexBuffer>();
		vb->m_buffer = std::move(buffer);
		vb->m_vertexCount = params.m_vertexCount;
		vb->m_vertexSize = params.m_data.size_bytes() / params.m_vertexCount;
		vb->m_bufferSize = params.m_data.size_bytes();
		return vb;
	}
	auto DX11RenderContext::CreateUniformBuffer(
		const IPipelineState& pipeline,
		const UniformBufferCreationParams& params)
		-> std::shared_ptr<IUniformBuffer>
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer{};
		D3D11_BUFFER_DESC desc{};
		desc.ByteWidth = params.m_size;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		auto hr = m_device->CreateBuffer(&desc, nullptr, buffer.GetAddressOf());
		if (FAILED(hr))
		{
			AlertFailed("Failed to create uniform buffer", hr);
			return nullptr;
		}
		auto ub = std::make_shared<DX11RenderContextUniformBuffer>();
		ub->m_buffer = std::move(buffer);
		ub->m_size = params.m_size;
		ub->m_includeInGeometryShader = params.m_includeInGeometryShader;
		ub->m_includeInVertexShader = params.m_includeInVertexShader;
		ub->m_includeInPixelShader = params.m_includeInPixelShader;
		ub->m_includeInComputeShader = params.m_includeInComputeShader;
		return ub;
	}
	auto DX11RenderContext::WriteUniformBuffer(const IUniformBuffer& buffer,
											   const void* data, oxySize size)
		-> void
	{
		const auto& ub =
			static_cast<const DX11RenderContextUniformBuffer&>(buffer);
		OXYCHECK(size == ub.m_size);
		m_deviceContext->UpdateSubresource(ub.m_buffer.Get(), 0, nullptr,
										   data, 0, 0);
	}
	auto DX11RenderContext::SetIndexBuffer(const IIndexBuffer& buffer) -> void
	{
		const auto& ib =
			static_cast<const DX11RenderContextIndexBuffer&>(buffer);
		DXGI_FORMAT format{};
		if (ib.m_indexSize == 1)
			format = DXGI_FORMAT_R8_UINT;
		else if (ib.m_indexSize == 2)
			format = DXGI_FORMAT_R16_UINT;
		else if (ib.m_indexSize == 4)
			format = DXGI_FORMAT_R32_UINT;
		m_deviceContext->IASetIndexBuffer(ib.m_buffer.Get(), format, 0);
	}
	auto DX11RenderContext::SetVertexBuffer(const IVertexBuffer& buffer) -> void
	{
		const auto& vb =
			static_cast<const DX11RenderContextVertexBuffer&>(buffer);
		UINT stride = vb.m_vertexSize;
		UINT offset = 0;
		m_deviceContext->IASetVertexBuffers(0, 1, vb.m_buffer.GetAddressOf(),
											&stride, &offset);
	}
	auto DX11RenderContext::SetPipelineState(const IPipelineState& pipeline)
		-> void
	{
		const auto& state =
			static_cast<const DX11RenderContextPipelineState&>(pipeline);
		if (state.m_vertexShader)
			m_deviceContext->VSSetShader(state.m_vertexShader.Get(), nullptr,
										 0);
		if (state.m_pixelShader)
			m_deviceContext->PSSetShader(state.m_pixelShader.Get(), nullptr, 0);
		if (state.m_geometryShader)
			m_deviceContext->GSSetShader(state.m_geometryShader.Get(), nullptr,
										 0);
		if (state.m_computeShader)
			m_deviceContext->CSSetShader(state.m_computeShader.Get(), nullptr,
										 0);
		if (state.m_rasterizerState)
			m_deviceContext->RSSetState(state.m_rasterizerState.Get());
		if (state.m_blendState)
			m_deviceContext->OMSetBlendState(state.m_blendState.Get(), nullptr,
											 0xFFFFFFFF);
		if (state.m_depthStencilState)
			m_deviceContext->OMSetDepthStencilState(
				state.m_depthStencilState.Get(), 0);
		if (state.m_layout)
			m_deviceContext->IASetInputLayout(state.m_layout.Get());

		// TODO: MORE PRIMITIVE TYPES
		m_deviceContext->IASetPrimitiveTopology(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
	auto DX11RenderContext::SetUniformBuffer(const IUniformBuffer& buffer,
											 oxyU8 slot)
		-> void
	{
		const auto& ub =
			static_cast<const DX11RenderContextUniformBuffer&>(buffer);
		if (ub.m_includeInGeometryShader)
			m_deviceContext->GSSetConstantBuffers(slot, 1,
												  ub.m_buffer.GetAddressOf());
		if (ub.m_includeInVertexShader)
			m_deviceContext->VSSetConstantBuffers(slot, 1,
												  ub.m_buffer.GetAddressOf());
		if (ub.m_includeInPixelShader)
			m_deviceContext->PSSetConstantBuffers(slot, 1,
												  ub.m_buffer.GetAddressOf());
		if (ub.m_includeInComputeShader)
			m_deviceContext->CSSetConstantBuffers(slot, 1,
												  ub.m_buffer.GetAddressOf());
	}
	auto DX11RenderContext::BindTexture2D(const ITexture2D& texture, oxyU8 slot)
		-> void 
	{
		const auto& tex = static_cast<const DX11Texture2D&>(texture);
		m_deviceContext->PSSetShaderResources(slot, 1, tex.m_srv.GetAddressOf());
	}
	auto DX11RenderContext::DrawIndexed(oxySize indexCount, oxySize indexOffset,
									oxySize vertexOffset) -> void
{
	m_deviceContext->DrawIndexed(indexCount, indexOffset, vertexOffset);
}
auto DX11RenderContext::DestroySwapChainResources() -> void
{
	m_backBuffer = nullptr;
	m_renderTargetView = nullptr;
	m_depthStencilBuffer = nullptr;
}
auto DX11RenderContext::CreateSwapChainResources() -> void
{
	auto hr = m_swapChain->GetBuffer(
		0, __uuidof(ID3D11Texture2D),
		reinterpret_cast<void**>(m_backBuffer.ReleaseAndGetAddressOf()));
	if (FAILED(hr))
	{
		AlertFailed("Failed to get back buffer", hr);
	}

	hr = m_device->CreateRenderTargetView(
		m_backBuffer.Get(), nullptr,
		m_renderTargetView.ReleaseAndGetAddressOf());
	if (FAILED(hr))
	{
		AlertFailed("Failed to create render target view", hr);
	}

	DXGI_SWAP_CHAIN_DESC desc{};
	hr = m_swapChain->GetDesc(&desc);
	if (FAILED(hr))
	{
		AlertFailed("Failed to get swap chain desc", hr);
	}

	// depth stencil
	D3D11_TEXTURE2D_DESC depthStencilDesc{};
	depthStencilDesc.Width = desc.BufferDesc.Width;
	depthStencilDesc.Height = desc.BufferDesc.Height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;
	hr = m_device->CreateTexture2D(
		&depthStencilDesc, nullptr,
		m_depthStencilBuffer.ReleaseAndGetAddressOf());
	if (FAILED(hr))
	{
		AlertFailed("Failed to create depth stencil", hr);
	}
	hr = m_device->CreateDepthStencilView(
		m_depthStencilBuffer.Get(), nullptr,
		m_depthStencilView.ReleaseAndGetAddressOf());
	if (FAILED(hr))
	{
		AlertFailed("Failed to create depth stencil view", hr);
	}
}
}
; // namespace oxygen

#endif