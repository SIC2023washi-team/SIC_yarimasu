#include "SceneGame.h"
#include"./Lemur/Graphics/Camera.h"
#include"./Lemur/Resource/ResourceManager.h"

#include"./Lemur/Effekseer/EffekseerManager.h"

void SceneGame::Initialize()
{
    Lemur::Graphics::Graphics& graphics = Lemur::Graphics::Graphics::Instance();
    SetState();

	HRESULT hr{ S_OK };
	// シーン定数バッファオブジェクトを生成
	{
		D3D11_BUFFER_DESC buffer_desc{};
		buffer_desc.Usage = D3D11_USAGE_DEFAULT;// 読み取りおよび書き込みがどのように行われるか
		buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;// バッファがパイプラインにどのようにバインド(結びつけ)されるかを特定
		buffer_desc.CPUAccessFlags = 0;// CPU アクセス フラグ（CPU アクセスが必要ない場合は 0）
		buffer_desc.MiscFlags = 0;// その他のフラグ（未使用に場合は0）
		buffer_desc.StructureByteStride = 0;//バッファが構造化バッファを表す場合の、バッファ構造内の各要素のサイズ
		{
			buffer_desc.ByteWidth = sizeof(scene_constants);// バッファのサイズ 
			hr = graphics.GetDevice()->CreateBuffer(&buffer_desc, nullptr, constant_buffers[0].GetAddressOf());
			_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
		}
		{
			buffer_desc.ByteWidth = sizeof(dissolve_constants);
			hr = graphics.GetDevice()->CreateBuffer(&buffer_desc, nullptr, dissolve_constant_buffer.GetAddressOf());
			_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
		}
	}

#if 0
	// BLOOM
	bloomer = std::make_unique<bloom>(graphics.GetDevice(), 1280, 720);
	create_ps_from_cso(graphics.GetDevice(), "./Shader/final_pass_ps.cso", pixel_shaders[0].ReleaseAndGetAddressOf());

	// SKYMAP
	bit_block_transfer_sky = std::make_unique<fullscreen_quad>(graphics.GetDevice());
	create_ps_from_cso(graphics.GetDevice(), "./Shader/skymap_ps.cso", pixel_shaders[1].GetAddressOf());
	load_texture_from_file(graphics.GetDevice(), L".\\resources\\winter_evening_4k.hdr", skymap.GetAddressOf(), graphics.GetTexture2D());

	// ZELDA
	create_ps_from_cso(graphics.GetDevice(), "./Shader/zelda_ps.cso", zelda_ps.GetAddressOf());

	// SHADOW
	skinned_meshes[1] = std::make_unique<skinned_mesh>(graphics.GetDevice(), ".\\resources\\grid.fbx");
	double_speed_z = std::make_unique<shadow_map>(graphics.GetDevice(), shadowmap_width, shadowmap_height);

	// MASK
	dummy_sprite = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\MASK\\chip_win.png");
	load_texture_from_file(graphics.GetDevice(), L".\\resources\\MASK\\dissolve_animation.png",
		mask_texture.GetAddressOf(), &mask_texture2dDesc);

	// sprite用デフォルト描画シェーダー（ディゾルブ）
	{
		D3D11_INPUT_ELEMENT_DESC input_element_desc[]
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		create_vs_from_cso(graphics.GetDevice(), "./Shader/sprite_dissolve_vs.cso", sprite_vertex_shader.GetAddressOf(),
			sprite_input_layout.GetAddressOf(), input_element_desc, ARRAYSIZE(input_element_desc));
		create_ps_from_cso(graphics.GetDevice(), "./Shader/sprite_dissolve_ps.cso", sprite_pixel_shader.GetAddressOf());
	}
#endif
}

void SceneGame::Finalize()
{
}

void SceneGame::Update(float elapsedTime)
{
	Camera& camera = Camera::Instance();

	// エフェクト更新処理
	EffectManager::Instance().Update(elapsedTime);

	camera.Update(elapsedTime);

	ImGui::Begin("ImGUI");

	ImGui::End();
}

void SceneGame::Render(float elapsedTime)
{
}
