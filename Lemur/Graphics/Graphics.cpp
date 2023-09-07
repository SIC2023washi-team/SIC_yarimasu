#include "Graphics.h"
#include "shader.h"
#include "texture.h"
#include "Camera.h"

namespace Lemur::Graphics
{
	Graphics* Graphics::instance = nullptr;

	Graphics::Graphics(HWND hwnd, bool fullscreen)
	{
		// インスタンス設定
		instance = this;

		HRESULT hr{ S_OK };

		// デバイス・デバイスコンテキスト・スワップチェーンの作成
		{
			UINT create_device_flags{ 0 };
#ifdef _DEBUG
			create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

			D3D_FEATURE_LEVEL feature_levels{ D3D_FEATURE_LEVEL_11_0 };

			DXGI_SWAP_CHAIN_DESC swap_chain_desc{};
			swap_chain_desc.BufferCount = 1;
			swap_chain_desc.BufferDesc.Width = SCREEN_WIDTH;// スクリーンサイズの設定
			swap_chain_desc.BufferDesc.Height = SCREEN_HEIGHT;
			swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//アルファを含むチャネルあたり 8 ビットをサポートする 4 コンポーネントの 32 ビット符号なし正規化整数形式。
			swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
			swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
			swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swap_chain_desc.OutputWindow = hwnd;	// 出力ウィンドウハンドル
			swap_chain_desc.SampleDesc.Count = 1;	// バックバッファの数（トータル２枚）
			swap_chain_desc.SampleDesc.Quality = 0;
			swap_chain_desc.Windowed = !fullscreen;	// これ以外のフルスクリーンの方法はx3dgp.fullscreen
			// デバイスの初期化と同時にスワップチェーンを初期化する場合
			hr = D3D11CreateDeviceAndSwapChain(
				NULL,
				D3D_DRIVER_TYPE_HARDWARE,
				NULL,
				create_device_flags,
				&feature_levels,
				1,
				D3D11_SDK_VERSION,
				&swap_chain_desc,
				swap_chain.GetAddressOf(),
				device.GetAddressOf(),
				NULL,
				immediate_context.GetAddressOf());

			_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

		}
		// レンダーターゲットビューの作成
		{
			Microsoft::WRL::ComPtr<ID3D11Texture2D> back_buffer{};
			// SwapChainから一枚もらう
			hr = swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(back_buffer.GetAddressOf()));
			_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
			// この時にRefCountが+1される
			// back_bufferから&render_target_viewを作る（viewのニュアンスは実体ではない）
			hr = device->CreateRenderTargetView(back_buffer.Get(), NULL, render_target_view.GetAddressOf());
			_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
		}

		// 深度ステンシルビューの作成
		{
			Microsoft::WRL::ComPtr<ID3D11Texture2D> depth_stencil_buffer{};
			texture2d_desc;
			texture2d_desc.Width = SCREEN_WIDTH;
			texture2d_desc.Height = SCREEN_HEIGHT;
			texture2d_desc.MipLevels = 1; // ミップマップの数
			texture2d_desc.ArraySize = 1;
			texture2d_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			texture2d_desc.SampleDesc.Count = 1;
			texture2d_desc.SampleDesc.Quality = 0;
			texture2d_desc.Usage = D3D11_USAGE_DEFAULT;
			texture2d_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			texture2d_desc.CPUAccessFlags = 0;
			texture2d_desc.MiscFlags = 0;
			hr = device->CreateTexture2D(&texture2d_desc, NULL, depth_stencil_buffer.GetAddressOf());
			_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

			D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc{};
			depth_stencil_view_desc.Format = texture2d_desc.Format;
			depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			depth_stencil_view_desc.Texture2D.MipSlice = 0;
			hr = device->CreateDepthStencilView(depth_stencil_buffer.Get(), &depth_stencil_view_desc, depth_stencil_view.GetAddressOf());
			_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
		}
		// ラスタライザステートオブジェクトを生成(前のステージで処理された点や三角形などを画面のピクセルに変換する)
		{
			D3D11_RASTERIZER_DESC rasterizer_desc{};
			rasterizer_desc.FillMode = D3D11_FILL_SOLID;
			rasterizer_desc.CullMode = D3D11_CULL_BACK;// 背中省かれる
			// 左手系右手系でここを変える
			rasterizer_desc.FrontCounterClockwise = TRUE;// 反時計回り（CCW）を前面とする（CW→時計回り）
			rasterizer_desc.DepthBias = 0;
			rasterizer_desc.DepthBiasClamp = 0;
			rasterizer_desc.SlopeScaledDepthBias = 0;
			rasterizer_desc.DepthClipEnable = TRUE;
			rasterizer_desc.ScissorEnable = FALSE;
			rasterizer_desc.MultisampleEnable = FALSE;
			rasterizer_desc.AntialiasedLineEnable = FALSE;
			hr = device->CreateRasterizerState(&rasterizer_desc, rasterizer_states[static_cast<size_t>(RASTER_STATE::SOLID)].GetAddressOf());
			_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

			rasterizer_desc.FillMode = D3D11_FILL_WIREFRAME;
			rasterizer_desc.CullMode = D3D11_CULL_BACK;
			rasterizer_desc.AntialiasedLineEnable = TRUE;
			hr = device->CreateRasterizerState(&rasterizer_desc, rasterizer_states[static_cast<size_t>(RASTER_STATE::WIREFRAME)].GetAddressOf());
			_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

			rasterizer_desc.FillMode = D3D11_FILL_SOLID;
			rasterizer_desc.CullMode = D3D11_CULL_NONE;
			rasterizer_desc.AntialiasedLineEnable = TRUE;
			hr = device->CreateRasterizerState(&rasterizer_desc, rasterizer_states[static_cast<size_t>(RASTER_STATE::CULL_NONE)].GetAddressOf());
			_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

			rasterizer_desc.FillMode = D3D11_FILL_WIREFRAME;
			rasterizer_desc.CullMode = D3D11_CULL_NONE;
			rasterizer_desc.AntialiasedLineEnable = TRUE;
			hr = device->CreateRasterizerState(&rasterizer_desc, rasterizer_states[static_cast<size_t>(RASTER_STATE::WIREFRAME_CULL_NONE)].GetAddressOf());
			_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
		}

		//　ビューポートの設定
		{
			D3D11_VIEWPORT viewport{};
			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Width = static_cast<float>(SCREEN_WIDTH);
			viewport.Height = static_cast<float>(SCREEN_HEIGHT);
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;
			// 画を描く場所を決める
			immediate_context->RSSetViewports(1, &viewport);
		}
	}

	void Graphics::initialize(HWND hwnd, bool fullscreen)
	{
	}

	void Graphics::render(float elapsed_time)
	{
		// ビューポートの設定
#if 0
		D3D11_VIEWPORT viewport;
		UINT num_viewports{ 1 };
		immediate_context->RSGetViewports(&num_viewports, &viewport);

		float aspect_ratio{ viewport.Width / viewport.Height };


		// 視線行列を生成
		DirectX::XMVECTOR eye{ DirectX::XMLoadFloat4(&camera_position) };
		DirectX::XMVECTOR focus{ DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f) };
		DirectX::XMVECTOR up{ DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) };
		DirectX::XMMATRIX V{ DirectX::XMMatrixLookAtLH(eye, focus, up) };

		// 射影行列を生成
		DirectX::XMMATRIX P{ DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(30), aspect_ratio, 0.1f, 100.0f) };
		bit_block_transfer->blit(immediate_context.Get(), framebuffers[1]->shader_resource_views[0].GetAddressOf(), 0, 1);
#endif
#if 0
		bit_block_transfer->blit(immediate_context.Get(), framebuffers[0]->shader_resource_views[0].GetAddressOf(), 0, 1);
#endif
		UINT sync_interval{ 0 };
		swap_chain->Present(sync_interval, 0);// FrontバッファとBackバッファを入れ替える
		// ↓この下にspriteしても何も出ない
	}
}