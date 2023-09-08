#include "Graphics.h"
#include "shader.h"
#include "texture.h"
#include "Camera.h"

namespace Lemur::Graphics
{
	Graphics* Graphics::instance = nullptr;

	Graphics::Graphics(HWND hwnd, bool fullscreen)
	{
		// �C���X�^���X�ݒ�
		instance = this;

		HRESULT hr{ S_OK };

		// �f�o�C�X�E�f�o�C�X�R���e�L�X�g�E�X���b�v�`�F�[���̍쐬
		{
			UINT create_device_flags{ 0 };
#ifdef _DEBUG
			create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

			D3D_FEATURE_LEVEL feature_levels{ D3D_FEATURE_LEVEL_11_0 };

			DXGI_SWAP_CHAIN_DESC swap_chain_desc{};
			swap_chain_desc.BufferCount = 1;
			swap_chain_desc.BufferDesc.Width = SCREEN_WIDTH;// �X�N���[���T�C�Y�̐ݒ�
			swap_chain_desc.BufferDesc.Height = SCREEN_HEIGHT;
			swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//�A���t�@���܂ރ`���l�������� 8 �r�b�g���T�|�[�g���� 4 �R���|�[�l���g�� 32 �r�b�g�����Ȃ����K�������`���B
			swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
			swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
			swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swap_chain_desc.OutputWindow = hwnd;	// �o�̓E�B���h�E�n���h��
			swap_chain_desc.SampleDesc.Count = 1;	// �o�b�N�o�b�t�@�̐��i�g�[�^���Q���j
			swap_chain_desc.SampleDesc.Quality = 0;
			swap_chain_desc.Windowed = !fullscreen;	// ����ȊO�̃t���X�N���[���̕��@��x3dgp.fullscreen
			// �f�o�C�X�̏������Ɠ����ɃX���b�v�`�F�[��������������ꍇ
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
		// �����_�[�^�[�Q�b�g�r���[�̍쐬
		{
			Microsoft::WRL::ComPtr<ID3D11Texture2D> back_buffer{};
			// SwapChain����ꖇ���炤
			hr = swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(back_buffer.GetAddressOf()));
			_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
			// ���̎���RefCount��+1�����
			// back_buffer����&render_target_view�����iview�̃j���A���X�͎��̂ł͂Ȃ��j
			hr = device->CreateRenderTargetView(back_buffer.Get(), NULL, render_target_view.GetAddressOf());
			_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
		}

		// �[�x�X�e���V���r���[�̍쐬
		{
			Microsoft::WRL::ComPtr<ID3D11Texture2D> depth_stencil_buffer{};
			texture2d_desc;
			texture2d_desc.Width = SCREEN_WIDTH;
			texture2d_desc.Height = SCREEN_HEIGHT;
			texture2d_desc.MipLevels = 1; // �~�b�v�}�b�v�̐�
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
		// ���X�^���C�U�X�e�[�g�I�u�W�F�N�g�𐶐�(�O�̃X�e�[�W�ŏ������ꂽ�_��O�p�`�Ȃǂ���ʂ̃s�N�Z���ɕϊ�����)
		{
			D3D11_RASTERIZER_DESC rasterizer_desc{};
			rasterizer_desc.FillMode = D3D11_FILL_SOLID;
			rasterizer_desc.CullMode = D3D11_CULL_BACK;// �w���Ȃ����
			// ����n�E��n�ł�����ς���
			rasterizer_desc.FrontCounterClockwise = TRUE;// �����v���iCCW�j��O�ʂƂ���iCW�����v���j
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

		//�@�r���[�|�[�g�̐ݒ�
		{
			D3D11_VIEWPORT viewport{};
			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Width = static_cast<float>(SCREEN_WIDTH);
			viewport.Height = static_cast<float>(SCREEN_HEIGHT);
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;
			// ���`���ꏊ�����߂�
			immediate_context->RSSetViewports(1, &viewport);
		}
	}

	void Graphics::initialize(HWND hwnd, bool fullscreen)
	{
	}

	void Graphics::render(float elapsed_time)
	{
		// �r���[�|�[�g�̐ݒ�
#if 0
		D3D11_VIEWPORT viewport;
		UINT num_viewports{ 1 };
		immediate_context->RSGetViewports(&num_viewports, &viewport);

		float aspect_ratio{ viewport.Width / viewport.Height };


		// �����s��𐶐�
		DirectX::XMVECTOR eye{ DirectX::XMLoadFloat4(&camera_position) };
		DirectX::XMVECTOR focus{ DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f) };
		DirectX::XMVECTOR up{ DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) };
		DirectX::XMMATRIX V{ DirectX::XMMatrixLookAtLH(eye, focus, up) };

		// �ˉe�s��𐶐�
		DirectX::XMMATRIX P{ DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(30), aspect_ratio, 0.1f, 100.0f) };
		bit_block_transfer->blit(immediate_context.Get(), framebuffers[1]->shader_resource_views[0].GetAddressOf(), 0, 1);
#endif
#if 0
		bit_block_transfer->blit(immediate_context.Get(), framebuffers[0]->shader_resource_views[0].GetAddressOf(), 0, 1);
#endif
		UINT sync_interval{ 0 };
		swap_chain->Present(sync_interval, 0);// Front�o�b�t�@��Back�o�b�t�@�����ւ���
		// �����̉���sprite���Ă������o�Ȃ�
	}
}