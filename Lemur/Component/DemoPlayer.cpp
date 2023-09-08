#include "DemoPlayer.h"

void DemoPlayerGraphicsComponent::Initialize(GameObject& gameobj)
{
    Lemur::Graphics::Graphics& graphics = Lemur::Graphics::Graphics::Instance();
    DemoPlayerModel= ResourceManager::Instance().LoadModelResource(graphics.GetDevice(), ".\\resources\\nico.fbx");
}

void DemoPlayerGraphicsComponent::Update(GameObject& gameobj)
{

}

void DemoPlayerGraphicsComponent::Render(GameObject& gameobj,float elapsedTime,ID3D11PixelShader* replaced_pixel_shader)
{
	Lemur::Graphics::Graphics& graphics = Lemur::Graphics::Graphics::Instance();

	ID3D11DeviceContext* immediate_context = graphics.GetDeviceContext();

	// ����n�EY ���A�b�v�֕ϊ�
	const DirectX::XMFLOAT4X4 coordinate_system_transforms[]{
		{ -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },	// 0:RHS Y-UP
		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },		// 1:LHS Y-UP
		{ -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 1 },	// 2:RHS Z-UP
		{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1 },		// 3:LHS Z-UP
	};
#if 0
	// �P�ʂ��Z���`���[�g�����烁�[�g���ɕύX����ɂ́A�uscale_factor�v�� 0.01 �ɐݒ�
	const float scale_factor = 1.0f; // To change the units from centimeters to meters, set 'scale_factor' to 0.01.
#else
	const float scale_factor = 0.01f; // To change the units from centimeters to meters, set 'scale_factor' to 0.01.
#endif
	// �ϊ��p
	DirectX::XMMATRIX C{ DirectX::XMLoadFloat4x4(&coordinate_system_transforms[0])* DirectX::XMMatrixScaling(scale_factor, scale_factor, scale_factor) };
	DirectX::XMMATRIX S{ DirectX::XMMatrixScaling(gameobj.scaling.x, gameobj.scaling.y, gameobj.scaling.z) };
	DirectX::XMMATRIX R{ DirectX::XMMatrixRotationRollPitchYaw(gameobj.rotation.x, gameobj.rotation.y, gameobj.rotation.z) };
	DirectX::XMMATRIX T{ DirectX::XMMatrixTranslation(gameobj.translation.x, gameobj.translation.y, gameobj.translation.z) };
	// ���[���h�ϊ��s����쐬
	DirectX::XMFLOAT4X4 world;
	DirectX::XMStoreFloat4x4(&world, C * S * R * T);


	if (DemoPlayerModel->animation_clips.size() > 0)
	{
		// �A�j���[�V�����p
		int clip_index = 0;
		int frame_index = 0;
		static float animation_tick = 0;
#if 1
		animation& animation{ DemoPlayerModel->animation_clips.at(clip_index) };
		frame_index = static_cast<int>(animation_tick * animation.sampling_rate);
		if (frame_index > animation.sequence.size() - 1)
		{
			frame_index = 0;
			animation_tick = 0;
		}
		else
		{
			animation_tick += elapsedTime;
		}
		animation::keyframe& keyframe{ animation.sequence.at(frame_index) };
#else
		animation::keyframe keyframe;
		const animation::keyframe* keyframes[2]{
			&skinned_meshes[0]->animation_clips.at(0).sequence.at(40),
			&skinned_meshes[0]->animation_clips.at(0).sequence.at(80)
		};
		skinned_meshes[0]->blend_animations(keyframes, factors[2], keyframe);
		skinned_meshes[0]->update_animation(keyframe);

# endif
		DemoPlayerModel->render(immediate_context, world, gameobj.material_color, &keyframe, replaced_pixel_shader);
	}
	else
	{
		DemoPlayerModel->render(immediate_context, world, gameobj.material_color, nullptr, replaced_pixel_shader);
	}
}

void DemoPlayerGraphicsComponent::ShadowRender(GameObject& gameobj, float elapsedTime)
{
	Lemur::Graphics::Graphics& graphics = Lemur::Graphics::Graphics::Instance();

	ID3D11DeviceContext* immediate_context = graphics.GetDeviceContext();

	// ����n�EY ���A�b�v�֕ϊ�
	const DirectX::XMFLOAT4X4 coordinate_system_transforms[]{
		{ -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },	// 0:RHS Y-UP
		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },		// 1:LHS Y-UP
		{ -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 1 },	// 2:RHS Z-UP
		{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1 },		// 3:LHS Z-UP
	};
#if 0
	// �P�ʂ��Z���`���[�g�����烁�[�g���ɕύX����ɂ́A�uscale_factor�v�� 0.01 �ɐݒ�
	const float scale_factor = 1.0f; // To change the units from centimeters to meters, set 'scale_factor' to 0.01.
#else
	const float scale_factor = 0.01f; // To change the units from centimeters to meters, set 'scale_factor' to 0.01.
#endif
	// �ϊ��p
	DirectX::XMMATRIX C{ DirectX::XMLoadFloat4x4(&coordinate_system_transforms[0])* DirectX::XMMatrixScaling(scale_factor, scale_factor, scale_factor) };
	DirectX::XMMATRIX S{ DirectX::XMMatrixScaling(gameobj.scaling.x, gameobj.scaling.y, gameobj.scaling.z) };
	DirectX::XMMATRIX R{ DirectX::XMMatrixRotationRollPitchYaw(gameobj.rotation.x, gameobj.rotation.y, gameobj.rotation.z) };
	DirectX::XMMATRIX T{ DirectX::XMMatrixTranslation(gameobj.translation.x, gameobj.translation.y, gameobj.translation.z) };
	// ���[���h�ϊ��s����쐬
	DirectX::XMFLOAT4X4 world;
	DirectX::XMStoreFloat4x4(&world, C * S * R * T);


	ID3D11PixelShader* null_pixel_shader{ NULL };

	if (DemoPlayerModel->animation_clips.size() > 0)
	{
		// �A�j���[�V�����p
		int clip_index = 0;
		int frame_index = 0;
		static float animation_tick = 0;
#if 1
		animation& animation{ DemoPlayerModel->animation_clips.at(clip_index) };
		frame_index = static_cast<int>(animation_tick * animation.sampling_rate);
		if (frame_index > animation.sequence.size() - 1)
		{
			frame_index = 0;
			animation_tick = 0;
		}
		else
		{
			animation_tick += elapsedTime;
		}
		animation::keyframe& keyframe{ animation.sequence.at(frame_index) };
#else
		animation::keyframe keyframe;
		const animation::keyframe* keyframes[2]{
			&skinned_meshes[0]->animation_clips.at(0).sequence.at(40),
			&skinned_meshes[0]->animation_clips.at(0).sequence.at(80)
		};
		skinned_meshes[0]->blend_animations(keyframes, factors[2], keyframe);
		skinned_meshes[0]->update_animation(keyframe);

# endif

		DemoPlayerModel->render(immediate_context, world, gameobj.material_color, &keyframe, null_pixel_shader);
	}
	else
	{
		DemoPlayerModel->render(immediate_context, world, gameobj.material_color, nullptr, null_pixel_shader);
	}
}

// ���͏���
void DemoPlayerInputComponent::Update(GameObject& gameobj, float elapsedTime)
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisRX();
	float ay = gamePad.GetAxisRY();

	float lx = gamePad.GetAxisLX();
	float ly = gamePad.GetAxisLY();
}
