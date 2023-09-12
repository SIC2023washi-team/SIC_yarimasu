#include "SceneGame.h"
#include <random>
#include "Lemur/Input/Mouse.h"
#include"./Lemur/Graphics/Camera.h"
#include"./Lemur/Resource/ResourceManager.h"

#include"./Lemur/Effekseer/EffekseerManager.h"
#include "GamePro_ProjectileStraight.h"

DirectX::XMFLOAT3 GiftAngle = { 0,0,0 };
DirectX::XMFLOAT4 GiftPosition = { 0,0,0,0 };



using namespace DirectX;
XMFLOAT4 convert_screen_to_world(LONG x/*screen*/, LONG y/*screen*/, float z/*ndc*/, D3D11_VIEWPORT vp, const DirectX::XMFLOAT4X4& view_projection)
{
	using namespace DirectX;
	XMFLOAT4 p;
	XMStoreFloat4(&p,
		XMVector3TransformCoord(
			XMVector3TransformCoord(
				XMVectorSet(static_cast<float>(x), static_cast<float>(y), z, 1),
				XMMatrixInverse(NULL,
					XMMatrixSet(
						vp.Width * 0.5f, 0.0f, 0.0f, 0.0f,
						0.0f, -vp.Height * 0.5f, 0.0f, 0.0f,
						0.0f, 0.0f, vp.MaxDepth - vp.MinDepth, 0.0f,
						vp.TopLeftX + vp.Width * 0.5f, vp.Height * 0.5f + vp.TopLeftY, vp.MinDepth, 1.0f))
			), XMMatrixInverse(NULL, XMLoadFloat4x4(&view_projection))
		)
	);
	return p;
}

void SceneGame::Initialize()
{
	Lemur::Graphics::Graphics& graphics = Lemur::Graphics::Graphics::Instance();
	SetState();

	HRESULT hr{ S_OK };
	// �V�[���萔�o�b�t�@�I�u�W�F�N�g�𐶐�
	{
		D3D11_BUFFER_DESC buffer_desc{};
		buffer_desc.Usage = D3D11_USAGE_DEFAULT;// �ǂݎ�肨��я������݂��ǂ̂悤�ɍs���邩
		buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;// �o�b�t�@���p�C�v���C���ɂǂ̂悤�Ƀo�C���h(���т�)����邩�����
		buffer_desc.CPUAccessFlags = 0;// CPU �A�N�Z�X �t���O�iCPU �A�N�Z�X���K�v�Ȃ��ꍇ�� 0�j
		buffer_desc.MiscFlags = 0;// ���̑��̃t���O�i���g�p�ɏꍇ��0�j
		buffer_desc.StructureByteStride = 0;//�o�b�t�@���\�����o�b�t�@��\���ꍇ�́A�o�b�t�@�\�����̊e�v�f�̃T�C�Y
		{
			buffer_desc.ByteWidth = sizeof(scene_constants);// �o�b�t�@�̃T�C�Y 
			hr = graphics.GetDevice()->CreateBuffer(&buffer_desc, nullptr, constant_buffers[0].GetAddressOf());
			_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
		}
		{
			buffer_desc.ByteWidth = sizeof(dissolve_constants);
			hr = graphics.GetDevice()->CreateBuffer(&buffer_desc, nullptr, dissolve_constant_buffer.GetAddressOf());
			_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
		}
	}

	//�l�̏�����
	ShopItemsNum[10] = {};
	SaveShopUi = {};
	shop_int = 0;
	UiCount = {};
	jank = 1000;
	isPaused = false;
	speed = 0.05f;
	damage = 5.0f;
	attack = 1.0f;
	HP = 1.0f;
	Player_HP = 3.0f;
	Player_MAXHP = 3.0f;

	speed_lv = 1;
	damage_lv = 1;
	attack_lv = 1;
	HP_lv = 1;
	Player_MAXHP_Lv = 1;
	speed_MAXlv = 10;
	damage_MAXlv = 10;
	attack_MAXlv = 10;
	HP_MAXlv = 10;
	Player_MAXHP_MAXLv = 10;

	// Stage
	stage = CreateStage();
	stage->Initialize();
	// Player
	player = CreatePlayer();
	player->Initialize();

	for (int i = 0; i < 5; i++)
	{
		addEnemy();
	}

	
	//pause�o�b�N
	addUi(3);
	//HP
	addUi(4);
	//shop
	addUi(5);
	//�W�����N�@����
	addUi(6);

	//HP
	addUi(1);
	//shop
	addUi(2);
	addUi(2);
	addUi(2);



	
	//for (auto& it : enemyList)
	//{
	//	it->Initialize();
	//}


	//enemy = CreateEnemy();
	//enemy->Initialize();

	//ui = CreateUi();
	//ui->Initialize();

	UiCount = {};

	framebuffers[0] = std::make_unique<framebuffer>(graphics.GetDevice(), 1280, 720);
	bit_block_transfer = std::make_unique<fullscreen_quad>(graphics.GetDevice());

	// ZELDA
	create_ps_from_cso(graphics.GetDevice(), "./Shader/zelda_ps.cso", zelda_ps.GetAddressOf());
	create_ps_from_cso(graphics.GetDevice(), "./Shader/stage_ps.cso", stage_ps.GetAddressOf());
	create_ps_from_cso(graphics.GetDevice(), "./Shader/character_ps.cso", chara_ps.GetAddressOf());

	player->pixelShader = chara_ps.Get();
	stage->pixelShader = stage_ps.Get();
	for (auto& it : enemyList)
	{
		it->pixelShader= chara_ps.Get();
	}
	for (auto& it : projectileList)
	{
		it->pixelShader = zelda_ps.Get();
	}
	// SHADOW
	//skinned_meshes[1] = std::make_unique<skinned_mesh>(graphics.GetDevice(), ".\\resources\\grid.fbx");
	double_speed_z = std::make_unique<shadow_map>(graphics.GetDevice(), shadowmap_width, shadowmap_height);


	// �q�b�g�G�t�F�N�g�ɃG�t�F�N�g�̃p�X������
	hitEffect = new Effect("resources/Effect/Hit.efk");


#if 0
	// BLOOM
	bloomer = std::make_unique<bloom>(graphics.GetDevice(), 1280, 720);
	create_ps_from_cso(graphics.GetDevice(), "./Shader/final_pass_ps.cso", pixel_shaders[0].ReleaseAndGetAddressOf());

	// SKYMAP
	bit_block_transfer_sky = std::make_unique<fullscreen_quad>(graphics.GetDevice());
	create_ps_from_cso(graphics.GetDevice(), "./Shader/skymap_ps.cso", pixel_shaders[1].GetAddressOf());
	load_texture_from_file(graphics.GetDevice(), L".\\resources\\winter_evening_4k.hdr", skymap.GetAddressOf(), graphics.GetTexture2D());

	// MASK
	dummy_sprite = std::make_unique<sprite>(graphics.GetDevice(), L".\\resources\\MASK\\chip_win.png");
	load_texture_from_file(graphics.GetDevice(), L".\\resources\\MASK\\dissolve_animation.png",
		mask_texture.GetAddressOf(), &mask_texture2dDesc);

	// sprite�p�f�t�H���g�`��V�F�[�_�[�i�f�B�]���u�j
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
	player->Delete();
	stage->Delete();

	//ui->Delete();

	//enemy->Delete();
	for (auto& it : enemyList)
	{
		it->Delete();
	}
	for (auto& it : UiList)
	{
		it->Delete();
	}
	for (auto& it : projectileList)
	{
		it->Delete();
	}
	enemyList.clear();
	UiList.clear();
	projectileList.clear();

	delete player;
	delete stage;
	//delete enemy;
}

void SceneGame::Update(HWND hwnd, float elapsedTime)
{
	UiGetUpdate();
	EnemyGetUpdate();

	Mouse& mouse = Input::Instance().GetMouse();

	for (auto& it : UiList)
	{
		it->Update(elapsedTime);

	}
	for (auto& it : UiList)
	{
		it->player_ = player;
		it->NumDelivery[5] = shop_int;
		if (it->NumDelivery[0] == 2)
		{
			it->NumDelivery[7] = jank;
		}
		if (it->NumDelivery[0] == 4)
		{
			it->NumDelivery[2] = Player_MAXHP;
			it->NumDelivery[1] = Player_HP;
		}
		if (it->NumDelivery[0] == 6)
		{
			it->NumDelivery[1] = jank;
		}
	}

	//if (mouse.GetButtonDown() == mouse.BTN_LEFT)
	//{
	//	if (!isPaused)
	//	{
	//		shop_int = 1;
	//		isPaused = true;
	//	}
	//	//else
	//	//{
	//	//	shop_int = 0;
	//	//	isPaused = false;


	//	//}
	//}



	if (isPaused)return;

	for (auto& it : enemyList)
	{
		it->player_ = player;
	}
	for (auto& it : projectileList)
	{
		it->player_ = player;
		it->enemyList_ = enemyList;
		
	}
	//enemy->player_ = player;
	player->enemy_ = enemy;
	player->projectile_ = projectile;

	Camera& camera = Camera::Instance();
	Lemur::Graphics::Graphics& graphics = Lemur::Graphics::Graphics::Instance();

	ID3D11DeviceContext* immediate_context = graphics.GetDeviceContext();

	// �G�t�F�N�g�X�V����
	EffectManager::Instance().Update(elapsedTime);

	camera.Update(elapsedTime);

	stage->Update(elapsedTime);

	player->Update(elapsedTime);

	//enemy->Update(elapsedTime);


	//ui->Update(elapsedTime);



	if (enemyList.size() != 0)
	{
		for (auto& it : enemyList)
		{
			it->Update(elapsedTime);

		}
	}
	if (projectileList.size() != 0)
	{
		for (auto& it : projectileList)
		{
			it->Update(elapsedTime);
		}
	}

	// ��m�[�h�̍폜

	auto it = enemyList.begin();
	while (it != enemyList.end())
	{
		if ((*it)->Death)
		{
			(*it)->Delete();
			it = enemyList.erase(it);
		}
		else
		{
			it++;
		}
	}
	auto Proj = projectileList.begin();
	while (Proj != projectileList.end())
	{
		if ((*Proj)->Death)
		{
			(*Proj)->Delete();
			Proj = projectileList.erase(Proj);
		}
		else
		{
			Proj++;
		}
	}

	auto Uiit = UiList.begin();
	while (Uiit != UiList.end())
	{
		if ((*Uiit)->Death)
		{
			(*Uiit)->Delete();
			Uiit = UiList.erase(Uiit);
		}
		else
		{
			Uiit++;
		}
	}
	//auto it = enemyList.begin();
	//while (it != enemyList.end())
	//{
	//	if(it->Death)
	//	{
	//		it = enemyList.erase(it);
	//	}
	//	else
	//	{
	//		it++;
	//	}
	//}
	//for (int i = 0; i < enemyList.size(); i++)
	//{
	//	if (enemyList[i]->Death)
	//	{
	//		enemyList.erase(i);
	//	}
	//}


	ProjectileVSEnemy();


	// �G�l�~�[���m�̓����蔻��
	{
		// �S�Ă̓G�Ƒ�������ŏՓ˔���
		int enemyCount = enemyList.size();
		for (int i = 0; i < enemyCount; ++i)
		{
			GameObject* enemyA = enemyList.at(i);
			for (int j = i + 1; j < enemyCount; ++j)
			{
				GameObject* enemyB = enemyList.at(j);
				// �Փ˔���
				DirectX::XMFLOAT3 outPosition;
				if (Collision::IntersectCylinderVsCylinder
				(enemyA->position,
					enemyA->radius,
					enemyA->height,
					enemyB->position,
					enemyB->radius,
					enemyB->height,
					outPosition)
					)
				{
					enemyB->position = outPosition;

					//const float power = 10.0f;
					//DirectX::XMFLOAT3 impulse;
					//DirectX::XMFLOAT3 e = enemyList.at(j)->position;
					//DirectX::XMFLOAT3 p = enemyList.at(i)->position;
					//float vx = e.x - p.x;
					//float vz = e.z - p.z;
					//float lengthXZ = sqrtf(vx * vx + vz * vz);
					////���K��
					//vx /= lengthXZ;
					//vz /= lengthXZ;
					//impulse.x = vx * power;
					//impulse.y = power * 0.5f;
					//impulse.z = vz * power;
					//enemyList.at(j)->AddImpulse(impulse);

				}
			}
		}
	}
	/////////////////////////////////////////////

	if (mouse.GetButtonDown() == mouse.BTN_LEFT)
	{
		
#if 0	
		scene_constants scene_data{};
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(hwnd, &p);

		D3D11_VIEWPORT viewports[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
		UINT viewport_count = { D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE };
		immediate_context->RSGetViewports(&viewport_count, viewports);
		XMFLOAT4X4 view_projection;
		XMStoreFloat4x4(&view_projection, Camera::Instance().GetViewMatrix()* Camera::Instance().GetProjectionMatrix());
		XMFLOAT4 position_on_near_plane = convert_screen_to_world(p.x, p.y, 0.0f, viewports[0], view_projection);
		DirectX::XMVECTOR WorldPosition0 = XMLoadFloat4(&position_on_near_plane);
#else
		DirectX::XMFLOAT3 screenPosition;
		screenPosition.x = static_cast<float>(mouse.GetOldPositionX());
		screenPosition.y = static_cast<float>(mouse.GetOldPositionY());
		screenPosition.z = 0.0f;

		D3D11_VIEWPORT viewport;
		UINT numViewports = 1;
		immediate_context->RSGetViewports(&numViewports, &viewport);

		DirectX::XMMATRIX View = Camera::Instance().GetViewMatrix();
		DirectX::XMMATRIX Projection = Camera::Instance().GetProjectionMatrix();

		DirectX::XMVECTOR WorldPosition0 = DirectX::XMVector3Unproject(
			DirectX::XMLoadFloat3(&screenPosition),
			viewport.TopLeftX, viewport.TopLeftY,
			viewport.Width, viewport.Height,
			viewport.MinDepth, viewport.MaxDepth,
			Projection, View, DirectX::XMMatrixIdentity()
		);
#endif

	

		XMVECTOR L0 = Camera::Instance().GetEye();
		XMFLOAT4 l0;
		XMStoreFloat4(&l0, L0);
		XMFLOAT4 l;
		XMStoreFloat4(&l, XMVector3Normalize(WorldPosition0 - L0));

		std::string intersected_mesh;
		std::string intersected_material;
		XMFLOAT3 intersected_normal;
		if (stage->stageModel->raycast(l0, l, stage->transform, intersection_point, intersected_normal, intersected_mesh, intersected_material))
		{
			OutputDebugStringA("Intersected : ");
			OutputDebugStringA(intersected_mesh.c_str());
			OutputDebugStringA(" : ");
			OutputDebugStringA(intersected_material.c_str());
			OutputDebugStringA("\n");

			///���@�̉�]
			//B-A�̃x�N�g��
			XMFLOAT3 rotationangle = { intersection_point.x - player->position.x,intersection_point.y - player->position.y,intersection_point.z - player->position.z };

			GiftPosition = intersection_point;
			GiftAngle = rotationangle;
			//���K��
			XMVECTOR tani = XMVector3Normalize(XMLoadFloat3(&rotationangle));

			player->rotation.y = atan2(rotationangle.x,rotationangle.z);
			
		}
		else
		{
			OutputDebugStringA("Unintersected...\n");
		}
		addProjectile();
	}

	if (mouse.GetButtonDown() == mouse.BTN_RIGHT)
	{
		// ����ōĐ��ł���
		hitEffect->Play(player->position);

	}

	ImGui::Begin("ImGUI");
	ImGui::SliderFloat("light_direction.x", &light_direction.x, -1.0f, +1.0f);
	ImGui::SliderFloat("light_direction.y", &light_direction.y, -1.0f, +1.0f);
	ImGui::SliderFloat("light_direction.z", &light_direction.z, -1.0f, +1.0f);

	//ImGui::SliderInt("", &numdebug, -10.0f, +10.0f);


	ImGui::SliderFloat("light_view_distance", &light_view_distance, 1.0f, +100.0f);
	ImGui::SliderFloat("light_view_size", &light_view_size, 1.0f, +100.0f);
	ImGui::SliderFloat("light_view_near_z", &light_view_near_z, 1.0f, light_view_far_z - 1.0f);
	ImGui::SliderFloat("light_view_far_z", &light_view_far_z, light_view_near_z + 1.0f, +100.0f);
	ImGui::End();

}

void SceneGame::Render(float elapsedTime)
{
	Camera& camera = Camera::Instance();
	Lemur::Graphics::Graphics& graphics = Lemur::Graphics::Graphics::Instance();

	//Debug
	graphics.debugRenderer = std::make_unique<DebugRenderer>(graphics.GetDevice());

	ID3D11DeviceContext* immediate_context = graphics.GetDeviceContext();
	ID3D11RenderTargetView* render_target_view = graphics.GetRenderTargetView();
	ID3D11DepthStencilView* depth_stencil_view = graphics.GetDepthStencilView();

	// bloom�p
	ID3D11RenderTargetView* null_render_target_views[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT]{};
	immediate_context->OMSetRenderTargets(_countof(null_render_target_views), null_render_target_views, 0);
	ID3D11ShaderResourceView* null_shader_resource_views[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT]{};
	immediate_context->VSSetShaderResources(0, _countof(null_shader_resource_views), null_shader_resource_views);
	immediate_context->PSSetShaderResources(0, _countof(null_shader_resource_views), null_shader_resource_views);

	// �����_�[�^�[�Q�b�g���̐ݒ�ƃN���A
	FLOAT color[]{ 0.2f, 0.2f, 0.2f, 1.0f };
	// �L�����o�X�S�̂��w�肵���F�ɓh��Ԃ�
	immediate_context->ClearRenderTargetView(render_target_view, color);
	// �L�����o�X�S�̂̉��s���������Z�b�g����
	immediate_context->ClearDepthStencilView(depth_stencil_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	// ���ꂩ��`���L�����o�X���w�肷��
	immediate_context->OMSetRenderTargets(1, &render_target_view, depth_stencil_view);

	immediate_context->PSSetSamplers(0, 1, sampler_states[static_cast<size_t>(SAMPLER_STATE::POINT)].GetAddressOf());
	immediate_context->PSSetSamplers(1, 1, sampler_states[static_cast<size_t>(SAMPLER_STATE::LINEAR)].GetAddressOf());
	immediate_context->PSSetSamplers(2, 1, sampler_states[static_cast<size_t>(SAMPLER_STATE::ANISOTROPIC)].GetAddressOf());
	immediate_context->PSSetSamplers(3, 1, sampler_states[static_cast<size_t>(SAMPLER_STATE::LINEAR_BORDER_BLACK)].GetAddressOf());
	immediate_context->PSSetSamplers(4, 1, sampler_states[static_cast<size_t>(SAMPLER_STATE::LINEAR_BORDER_WHITE)].GetAddressOf());
	// SHADOW
	immediate_context->PSSetSamplers(5, 1, sampler_states[static_cast<size_t>(SAMPLER_STATE::COMPARISON_LINEAR_BORDER_WHITE)].GetAddressOf());

	// �u�����h�X�e�[�g�̐ݒ�
	immediate_context->OMSetBlendState(blend_states[static_cast<size_t>(BLEND_STATE::ALPHA)].Get(), nullptr, 0xFFFFFFFF);
	// �[�x�X�e���V���X�e�[�g�̐ݒ�
	immediate_context->OMSetDepthStencilState(depth_stencil_states[static_cast<size_t>(DEPTH_STATE::ZT_ON_ZW_ON)].Get(), 0);
	immediate_context->RSSetState(rasterizer_states[static_cast<size_t>(RASTER_STATE::SOLID)].Get());

	camera.SetPerspectiveFov(immediate_context);

	// �萔�o�b�t�@�̍X�V
	scene_constants data{};
	data.light_direction = light_direction;
	DirectX::XMStoreFloat4(&data.camera_position, camera.GetEye());

#if 0

	D3D11_VIEWPORT viewport;
	UINT num_viewports{ 1 };
	immediate_context->RSGetViewports(&num_viewports, &viewport);

	float aspect_ratio{ viewport.Width / viewport.Height };

	// SKYMAP
	DirectX::XMStoreFloat4x4(&data.inv_view_projection, DirectX::XMMatrixInverse(NULL, camera.GetViewMatrix() * camera.GetProjectionMatrix()));

	immediate_context->UpdateSubresource(constant_buffers[0].Get(), 0, 0, &data, 0, 0);
	immediate_context->VSSetConstantBuffers(1, 1, constant_buffers[0].GetAddressOf());
	immediate_context->PSSetConstantBuffers(1, 1, constant_buffers[0].GetAddressOf());

	//3D�`��
	{
		framebuffers[0]->clear(immediate_context);
		framebuffers[0]->activate(immediate_context);
		immediate_context->OMSetDepthStencilState(depth_stencil_states[static_cast<size_t>(DEPTH_STATE::ZT_ON_ZW_ON)].Get(), 0);
		immediate_context->RSSetState(rasterizer_states[static_cast<size_t>(RASTER_STATE::SOLID)].Get());
		player->Render(elapsedTime);
		framebuffers[0]->deactivate(immediate_context);
		// BLOOM
		bloomer->make(immediate_context, framebuffers[0]->shader_resource_views[0].Get());

		immediate_context->OMSetDepthStencilState(depth_stencil_states[static_cast<size_t>(DEPTH_STATE::ZT_OFF_ZW_OFF)].Get(), 0);
		immediate_context->RSSetState(rasterizer_states[static_cast<size_t>(RASTER_STATE::CULL_NONE)].Get());
		immediate_context->OMSetBlendState(blend_states[static_cast<size_t>(BLEND_STATE::ALPHA)].Get(), nullptr, 0xFFFFFFFF);

		ID3D11ShaderResourceView* shader_resource_views[] =
		{
			framebuffers[0]->shader_resource_views[0].Get(),
			bloomer->shader_resource_view(),
		};
		bit_block_transfer->blit(immediate_context, shader_resource_views, 0, 2, pixel_shaders[0].Get());
	}
	// SKYMAP
	//immediate_context->OMSetDepthStencilState(depth_stencil_states[static_cast<size_t>(DEPTH_STATE::ZT_OFF_ZW_OFF)].Get(), 0);
	//immediate_context->RSSetState(rasterizer_states[static_cast<size_t>(RASTER_STATE::CULL_NONE)].Get());
	//bit_block_transfer_sky->blit(immediate_context, skymap.GetAddressOf(), 0, 1, pixel_shaders[1].Get());
	//

#endif
	// SHADOW : make shadow map
	{
		using namespace DirectX;

		const float aspect_ratio = double_speed_z->viewport.Width / double_speed_z->viewport.Height;
		XMVECTOR F{ XMLoadFloat4(&light_view_focus) };
		XMVECTOR E{ F - XMVector3Normalize(XMLoadFloat4(&light_direction)) * light_view_distance };
		XMVECTOR U{ XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) };
		XMMATRIX V{ XMMatrixLookAtLH(E, F, U) };
		XMMATRIX P{ XMMatrixOrthographicLH(light_view_size * aspect_ratio, light_view_size, light_view_near_z, light_view_far_z) };

		DirectX::XMStoreFloat4x4(&data.view_projection, V * P);
		data.light_view_projection = data.view_projection;
		immediate_context->UpdateSubresource(constant_buffers[0].Get(), 0, 0, &data, 0, 0);
		immediate_context->VSSetConstantBuffers(1, 1, constant_buffers[0].GetAddressOf());

		double_speed_z->clear(immediate_context, 1.0f);
		double_speed_z->activate(immediate_context);

		ID3D11PixelShader* null_pixel_shader{ NULL };
		player->Render(elapsedTime);

		double_speed_z->deactivate(immediate_context);
	}
	// Render scene
	D3D11_VIEWPORT viewport;
	UINT num_viewports{ 1 };
	immediate_context->RSGetViewports(&num_viewports, &viewport);
	DirectX::XMStoreFloat4x4(&data.view_projection, camera.GetViewMatrix() * camera.GetProjectionMatrix());

	immediate_context->UpdateSubresource(constant_buffers[0].Get(), 0, 0, &data, 0, 0);
	immediate_context->VSSetConstantBuffers(1, 1, constant_buffers[0].GetAddressOf());
	immediate_context->PSSetConstantBuffers(1, 1, constant_buffers[0].GetAddressOf());

	// SHADOW : bind shadow map at slot 8
	immediate_context->PSSetShaderResources(8, 1, double_speed_z->shader_resource_view.GetAddressOf());
	player->Render(elapsedTime);

	stage->Render(elapsedTime);


	//enemy->Render(elapsedTime);
	for (auto& it:enemyList)
	{
		it->Render(elapsedTime);
	}

	for (auto& it : projectileList)
	{
		it->Render(elapsedTime);
	}


#if  0


	D3D11_VIEWPORT viewport;
	UINT num_viewports{ 1 };
	immediate_context->RSGetViewports(&num_viewports, &viewport);

	float aspect_ratio{ viewport.Width / viewport.Height };

	// SKYMAP
	DirectX::XMStoreFloat4x4(&data.inv_view_projection, DirectX::XMMatrixInverse(NULL, camera.GetViewMatrix() * camera.GetProjectionMatrix()));

	immediate_context->UpdateSubresource(constant_buffers[0].Get(), 0, 0, &data, 0, 0);
	immediate_context->VSSetConstantBuffers(1, 1, constant_buffers[0].GetAddressOf());
	immediate_context->PSSetConstantBuffers(1, 1, constant_buffers[0].GetAddressOf());

	//3D�`��
	{
		framebuffers[0]->clear(immediate_context);
		framebuffers[0]->activate(immediate_context);
		immediate_context->OMSetDepthStencilState(depth_stencil_states[static_cast<size_t>(DEPTH_STATE::ZT_ON_ZW_ON)].Get(), 0);
		immediate_context->RSSetState(rasterizer_states[static_cast<size_t>(RASTER_STATE::SOLID)].Get());
		player->Render(elapsedTime);
		framebuffers[0]->deactivate(immediate_context);
		// BLOOM
		bloomer->make(immediate_context, framebuffers[0]->shader_resource_views[0].Get());

		immediate_context->OMSetDepthStencilState(depth_stencil_states[static_cast<size_t>(DEPTH_STATE::ZT_OFF_ZW_OFF)].Get(), 0);
		immediate_context->RSSetState(rasterizer_states[static_cast<size_t>(RASTER_STATE::CULL_NONE)].Get());
		immediate_context->OMSetBlendState(blend_states[static_cast<size_t>(BLEND_STATE::ALPHA)].Get(), nullptr, 0xFFFFFFFF);

		ID3D11ShaderResourceView* shader_resource_views[] =
		{
			framebuffers[0]->shader_resource_views[0].Get(),
			bloomer->shader_resource_view(),
		};
		bit_block_transfer->blit(immediate_context, shader_resource_views, 0, 2, pixel_shaders[0].Get());
	}
	// SKYMAP
	//immediate_context->OMSetDepthStencilState(depth_stencil_states[static_cast<size_t>(DEPTH_STATE::ZT_OFF_ZW_OFF)].Get(), 0);
	//immediate_context->RSSetState(rasterizer_states[static_cast<size_t>(RASTER_STATE::CULL_NONE)].Get());
	//bit_block_transfer_sky->blit(immediate_context, skymap.GetAddressOf(), 0, 1, pixel_shaders[1].Get());
	//

	// SHADOW : make shadow map
	{
		using namespace DirectX;

		const float aspect_ratio = double_speed_z->viewport.Width / double_speed_z->viewport.Height;
		XMVECTOR F{ XMLoadFloat4(&light_view_focus) };
		XMVECTOR E{ F - XMVector3Normalize(XMLoadFloat4(&light_direction)) * light_view_distance };
		XMVECTOR U{ XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) };
		XMMATRIX V{ XMMatrixLookAtLH(E, F, U) };
		XMMATRIX P{ XMMatrixOrthographicLH(light_view_size * aspect_ratio, light_view_size, light_view_near_z, light_view_far_z) };

		DirectX::XMStoreFloat4x4(&data.view_projection, V * P);
		data.light_view_projection = data.view_projection;
		immediate_context->UpdateSubresource(constant_buffers[0].Get(), 0, 0, &data, 0, 0);
		immediate_context->VSSetConstantBuffers(1, 1, constant_buffers[0].GetAddressOf());

		double_speed_z->clear(immediate_context, 1.0f);
		double_speed_z->activate(immediate_context);

		ID3D11PixelShader* null_pixel_shader{ NULL };
		// ������Render
		double_speed_z->deactivate(immediate_context);
	}

	DirectX::XMStoreFloat4x4(&data.view_projection, camera.GetViewMatrix() * camera.GetProjectionMatrix());

	// Render scene
	D3D11_VIEWPORT viewport;
	UINT num_viewports{ 1 };
	immediate_context->RSGetViewports(&num_viewports, &viewport);
	DirectX::XMStoreFloat4x4(&data.view_projection, camera.GetViewMatrix() * camera.GetProjectionMatrix());

	immediate_context->UpdateSubresource(constant_buffers[0].Get(), 0, 0, &data, 0, 0);
	immediate_context->VSSetConstantBuffers(1, 1, constant_buffers[0].GetAddressOf());
	immediate_context->PSSetConstantBuffers(1, 1, constant_buffers[0].GetAddressOf());

	// SHADOW : bind shadow map at slot 8
	immediate_context->PSSetShaderResources(8, 1, double_speed_z->shader_resource_view.GetAddressOf());

	// ������Render
#endif
		// 3D�G�t�F�N�g�`��
	{
		DirectX::XMFLOAT4X4 view{};
		DirectX::XMFLOAT4X4 projection{};

		DirectX::XMStoreFloat4x4(&view, camera.GetViewMatrix());
		DirectX::XMStoreFloat4x4(&projection, camera.GetProjectionMatrix());

		EffectManager::Instance().Render(view, projection);

		// �f�o�b�O�����_���`����s
		graphics.GetDebugRenderer()->Render(graphics.GetDeviceContext(), view, projection);

	}



	// sprite�`��

			immediate_context->OMSetDepthStencilState(depth_stencil_states[static_cast<size_t>(DEPTH_STATE::ZT_OFF_ZW_OFF)].Get(), 0);
			immediate_context->RSSetState(rasterizer_states[static_cast<size_t>(RASTER_STATE::CULL_NONE)].Get());
			immediate_context->OMSetBlendState(blend_states[static_cast<size_t>(BLEND_STATE::ALPHA)].Get(), nullptr, 0xFFFFFFFF);

			immediate_context->IASetInputLayout(sprite_input_layout.Get());
			immediate_context->VSSetShader(sprite_vertex_shader.Get(), nullptr, 0);
			immediate_context->PSSetShader(sprite_pixel_shader.Get(), nullptr, 0);
			immediate_context->PSSetSamplers(0, 1, sampler_states[static_cast<size_t>(SAMPLER_STATE::LINEAR)].GetAddressOf());
			immediate_context->PSSetShaderResources(1, 1, mask_texture.GetAddressOf());

			// �萔�o�b�t�@�̍X�V�i�f�B�]���u�j
			{
				dissolve_constants dissolve{};
				dissolve.parameters.x = dissolve_value;
				immediate_context->UpdateSubresource(dissolve_constant_buffer.Get(), 0, 0, &dissolve, 0, 0);
				immediate_context->VSSetConstantBuffers(3, 1, dissolve_constant_buffer.GetAddressOf());
				immediate_context->PSSetConstantBuffers(3, 1, dissolve_constant_buffer.GetAddressOf());
			}
			//dummy_sprite->render(immediate_context, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

			//ui->Render(elapsedTime);
			for (auto& it : UiList)
			{
				it->Render(elapsedTime);
			}

	{
		immediate_context->OMSetDepthStencilState(depth_stencil_states[static_cast<size_t>(DEPTH_STATE::ZT_OFF_ZW_OFF)].Get(), 0);
		immediate_context->RSSetState(rasterizer_states[static_cast<size_t>(RASTER_STATE::CULL_NONE)].Get());
		immediate_context->OMSetBlendState(blend_states[static_cast<size_t>(BLEND_STATE::ALPHA)].Get(), nullptr, 0xFFFFFFFF);

		immediate_context->IASetInputLayout(sprite_input_layout.Get());
		immediate_context->VSSetShader(sprite_vertex_shader.Get(), nullptr, 0);
		immediate_context->PSSetShader(sprite_pixel_shader.Get(), nullptr, 0);
		immediate_context->PSSetSamplers(0, 1, sampler_states[static_cast<size_t>(SAMPLER_STATE::LINEAR)].GetAddressOf());
		immediate_context->PSSetShaderResources(1, 1, mask_texture.GetAddressOf());

		// �萔�o�b�t�@�̍X�V�i�f�B�]���u�j
		{
			dissolve_constants dissolve{};
			dissolve.parameters.x = dissolve_value;
			immediate_context->UpdateSubresource(dissolve_constant_buffer.Get(), 0, 0, &dissolve, 0, 0);
			immediate_context->VSSetConstantBuffers(3, 1, dissolve_constant_buffer.GetAddressOf());
			immediate_context->PSSetConstantBuffers(3, 1, dissolve_constant_buffer.GetAddressOf());
		}
	}




}

void SceneGame::addEnemy()
{
	GameObject* e;
	e = CreateEnemy();
	e->Initialize();
	enemyList.push_back(e);
}

void SceneGame::addProjectile()
{
	GameObject* p;
	p = CreateProjectile();
	p->NumFloatDelivery[0] = GiftAngle.x;
	p->NumFloatDelivery[1] = GiftAngle.z;
	p->NumFloatDelivery[2] = speed;
	p->NumDelivery[3] = damage;
	p->NumDelivery[4] = HP;
	p->Initialize();
	projectileList.push_back(p);
}

void SceneGame::ProjectileVSEnemy()
{
	//TODO �e�ƓG�̂̓����蔻��
	if(enemyList.size()!=0&& projectileList.size() != 0)
	{
		// ��������ŏՓ˔���
		int enemyCount = enemyList.size();
		for (int i = 0; i < enemyCount; ++i)
		{
			GameObject* ene = enemyList.at(i);
			int projectileCount = projectileList.size();
			for (int j = 0; j < projectileCount; ++j)
			{
				GameObject* pro = projectileList.at(j);
				// �Փ˔���
				DirectX::XMFLOAT3 outPosition;
				if (Collision::IntersectSphereVsCylinder
				(pro->position,
					pro->radius,
					ene->position,
					ene->radius,
					ene->height,
					outPosition)
					)
				{
					ene->Death = true;
					//�������肢���܂�

				}
			}
		}
	}
}

void SceneGame::addUi(int Uitype)
{
	bool judge = false;
	GameObject* Ui;
	Ui = CreateUi();
	Ui->NumDelivery[0] = Uitype;
	if (Uitype == 4)Ui->NumDelivery[1] = Player_HP;
	if (Uitype == 4)Ui->NumDelivery[2] = Player_MAXHP;
	
	if (Uitype == 2)
	{
		std::mt19937 mt{ std::random_device{}() };
		for (int i = 0; i < 1;)
		{
			std::uniform_int_distribution<int> Type(0, 4);
			ShopItemsNum[SaveShopUi] = int(Type(mt));
			judge = false;
			for (int j = 0; j < SaveShopUi; j++)
			{

				if (ShopItemsNum[SaveShopUi] == ShopItemsNum[j])
				{
					judge = true;
					break;
				}

			}
			if (!judge)
			{
				break;
			}
			continue;
		}
		Ui->NumDelivery[2] = ShopItemsNum[SaveShopUi];
		Ui->NumDelivery[1] = SaveShopUi;
		switch (ShopItemsNum[SaveShopUi])
		{
		case 0:
			//�U�����x
			if (Uitype == 2)Ui->NumDelivery[3] = attack_lv;
			if (Uitype == 2)Ui->NumDelivery[4] = attack_MAXlv;
			break;
		case 1:
			//�e���x
			if (Uitype == 2)Ui->NumDelivery[3] = speed_lv;
			if (Uitype == 2)Ui->NumDelivery[4] = speed_MAXlv;
			break;
		case 2:
			//�ђʗ�
			if (Uitype == 2)Ui->NumDelivery[3] = HP_lv;
			if (Uitype == 2)Ui->NumDelivery[4] =HP_MAXlv;
			break;
		case 3:
			//�U����
			if (Uitype == 2)Ui->NumDelivery[3] = damage_lv;
			if (Uitype == 2)Ui->NumDelivery[4] = damage_MAXlv;
			break;
		case 4:
			//�v���C���[
			if (Uitype == 2)Ui->NumDelivery[3] = Player_MAXHP_Lv;

			if (Uitype == 2)Ui->NumDelivery[4] = Player_MAXHP_MAXLv;


			break;
		}
	}



	Ui->Initialize();
	
	UiList.push_back(Ui);

	if (Uitype == 2)SaveShopUi++;

	UiCount++;
	
}

void SceneGame::UiGetUpdate()
{
	bool judge = false;
	for (auto& it : UiList)
	{
		//Uitype2�B�\�͑�����UI�̒T��
		if (it->NumDelivery[0] == 2)
		{
			if (it->NumDelivery[6] == 1)
			{
				switch (it->NumDelivery[2])
				{
				case 0:
					//�U�����x
					attack += it->NumDelivery[6];
					it->NumDelivery[6] = 0;
					jank -= 100;
					break;
				case 1:
					//�e���x
					speed += 0.01f;
					it->NumDelivery[6] = 0;
					jank -= 100;
					break;
				case 2:
					//�ђʗ�
					HP += it->NumDelivery[6];
					it->NumDelivery[6] = 0;
					jank -= 100;
					break;
				case 3:
					//�U����
					damage += 5;
					it->NumDelivery[6] = 0;
					jank -= 100;
					break;
				case 4:
					//�v���C���[
					Player_HP += it->NumDelivery[6];
					Player_MAXHP += it->NumDelivery[6];
					it->NumDelivery[6] = 0;
					jank -= 100;

					break;
				}
				std::mt19937 mt{ std::random_device{}() };
				int newshopitems;
				for (int i = 0; i < 1;)
				{
					std::uniform_int_distribution<int> Type(0, 4);
					newshopitems = int(Type(mt));
					judge = false;
					for (int j = 0; j < SaveShopUi; j++)
					{
						if (newshopitems == ShopItemsNum[j])
						{
							judge = true;
							break;
						}

					}
					if (!judge)
					{
						break;
					}
					continue;
				}
				ShopItemsNum[it->NumDelivery[1]] = newshopitems;
				it->NumDelivery[2] = newshopitems;
				shop_int = 0;
				isPaused = false;
				it->Initialize();
				for (auto& it : UiList)
				{
					if (it->NumDelivery[0] == 5)
					{
						it->NumDelivery[6] = 0;
					}
				}
			}
		}
		//UItype5 shop
		if (it->NumDelivery[0] == 5)
		{
			if (it->NumDelivery[6] == 1)
			{
				
				shop_int = 1;
				isPaused = true;
			}
			else
			{
				
				shop_int = 0;
				isPaused = false;
			}
		}


	}


}

void SceneGame::EnemyGetUpdate()
{

	for (auto& it : enemyList)
	{

		if (it->NumDelivery[0] >= 1)
		{
			Player_HP -= it->NumDelivery[0];
			it->NumDelivery[0] = 0;
			it->NumDelivery[1] = 1;
		}
		if (it->NumDelivery[3] >= 1)
		{
			
			jank += it->NumDelivery[2];
			it->NumDelivery[3] = 0;
			it->NumDelivery[4]++;
		}

	}
}
//
//GamePro_ProjectileStraight* SceneGame::CreateProjectile()
//{
//	return new GamePro_ProjectileStraight(
//		new GamePro_ProjectileStraightInputComponent(),
//		new GamePro_ProjectileStraightPhysicsComponent(),
//		new GamePro_ProjectileStraightGraphicsComponent()
//	);
//
//}

