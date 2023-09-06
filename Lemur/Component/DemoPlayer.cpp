#include "GameObject.h"
#include "DemoPlayer.h"
#include "Lemur/Input/Mouse.h"
#include "Lemur/Graphics/Camera.h"

#define PlayerHitPoint 3.0f

void DemoPlayerPhysicsComponent::Initialize(GameObject& gameobj)
{
	gameobj.HitPoint = PlayerHitPoint;
}

void DemoPlayerPhysicsComponent::Update(GameObject& gameobj, float elapsedTime)
{
	/////�G�ɐڐG�����Ƃ�/////
	//if (gameobj.HitPoint != 0 && /*�_���[�W��H�炤*/)
	//{
	//	gameobj.HitPoint--;
	//}

	/////�}�E�X�̃N���b�N/////
	//if (/*���N���b�N�����Ƃ�*/)
	//{
	//	/////�e�̔���/////
	//	///�����̎擾///
	//	sqrtf(((gameobj.rotation.x - 0.0f) * (gameobj.rotation.x - 0.0f)) + ((gameobj.rotation.y - 0.0f) * (gameobj.rotation.y - 0.0f)) + ((gameobj.rotation.z - 0.0f) * (gameobj.rotation.z - 0.0f)));

	//}

	
	
}

void DemoPlayerGraphicsComponent::Initialize(GameObject& gameobj)
{
    Lemur::Graphics::Graphics& graphics = Lemur::Graphics::Graphics::Instance();
    DemoPlayerModel= ResourceManager::Instance().LoadModelResource(graphics.GetDevice(), ".\\resources\\botcanon_test.fbx");
}

void DemoPlayerGraphicsComponent::Update(GameObject& gameobj)
{

}

void DemoPlayerGraphicsComponent::Render(GameObject& gameobj,float elapsedTime)
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
		DemoPlayerModel->render(immediate_context, world, gameobj.material_color, &keyframe);
	}
	else
	{
		DemoPlayerModel->render(immediate_context, world, gameobj.material_color, nullptr);
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

	/*gameobj.rotation.y += lx * elapsedTime;
	gameobj.rotation.y += ly * elapsedTime;*/

	

	Mouse& mouse = Input::Instance().GetMouse();

	gameobj.rotation.y = mouse.GetPositionX() + SCREEN_WIDTH / 2;
	gameobj.rotation.y = mouse.GetPositionY() + SCREEN_HEIGHT / 2;

	//�r���[�|�[�g
	D3D11_VIEWPORT viewport;
	UINT numViewports = 1;
	//dc->RSGetViewports(&numViewports, &viewport);

	//�ϊ��s��
	DirectX::XMMATRIX View = Camera::Instance().GetViewMatrix();
	DirectX::XMMATRIX Projection = Camera::Instance().GetProjectionMatrix();
	DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();


	//if (mouse.GetButtonDown() == mouse.BTN_LEFT)
	//{
	////�}�E�X�J�[�\�����W
	//DirectX::XMFLOAT3 screenPosition;
	//screenPosition.x = static_cast<float>(mouse.GetOldPositionX());
	//screenPosition.y = static_cast<float>(mouse.GetOldPositionY());
	//screenPosition.z = 0.0f;
	//
	//DirectX::XMVECTOR WorldPosition0 = DirectX::XMVector3Unproject(
	//	DirectX::XMLoadFloat3(&screenPosition),
	//	viewport.TopLeftX, viewport.TopLeftY,
	//	viewport.Width, viewport.Height,
	//	viewport.MinDepth, viewport.MaxDepth,
	//	Projection, View, World
	//);
	//
	//DirectX::XMVECTOR WorldPosition1 = DirectX::XMVector3Unproject(
	//	DirectX::XMLoadFloat3(&screenPosition),
	//	viewport.TopLeftX, viewport.TopLeftY,
	//	viewport.Width, viewport.Height,
	//	viewport.MinDepth, viewport.MaxDepth,
	//	Projection, View, World
	//);
	//
	//DirectX::XMFLOAT3 worldPosition0;
	//DirectX::XMFLOAT3 worldPosition1;
	//DirectX::XMStoreFloat3(&worldPosition0, WorldPosition0);
	//DirectX::XMStoreFloat3(&worldPosition1, WorldPosition1);
	//
	//DirectX::XMFLOAT3 start = worldPosition0;
	//DirectX::XMFLOAT3 end = worldPosition1;
	//HitResult hit;

	//if (Stage::Instance().RayCast(start, end, hit))
	//{

	//}
}
