#include "GamePro_ProjectileStraight.h"



//void GamePro_ProjectileStraight::Launch(GameObject* gameobj, const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& position)
//{
//    GamePro_ProjectileStraight* project = dynamic_cast<GamePro_ProjectileStraight*> (gameobj);
//    project->direction = direction;
//    project->position = position;
//}

void GamePro_ProjectileStraightGraphicsComponent::Initialize(GameObject* gameobj)
{
    Lemur::Graphics::Graphics& graphics = Lemur::Graphics::Graphics::Instance();
    ID3D11DeviceContext* immediate_context = graphics.GetDeviceContext();
    BulletModel = ResourceManager::Instance().LoadModelResource(graphics.GetDevice(), ".\\resources\\Model\\bot\\botcanon_player_v001.fbx");
}

void GamePro_ProjectileStraightGraphicsComponent::Update(GameObject* gameobj)
{
}

void GamePro_ProjectileStraightGraphicsComponent::Render(GameObject* gameobj, float elapsedTime, ID3D11PixelShader* replaced_pixel_shader)
{
    GamePro_ProjectileStraight* project = dynamic_cast<GamePro_ProjectileStraight*> (gameobj);
    Lemur::Graphics::Graphics& graphics = Lemur::Graphics::Graphics::Instance();
    ID3D11DeviceContext* immediate_context = graphics.GetDeviceContext();


	// 左手系・Y 軸アップへ変換
	const DirectX::XMFLOAT4X4 coordinate_system_transforms[]{
		{ -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },	// 0:RHS Y-UP
		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },		// 1:LHS Y-UP
		{ -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 1 },	// 2:RHS Z-UP
		{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1 },		// 3:LHS Z-UP
	};
#if 0
	// 単位をセンチメートルからメートルに変更するには、「scale_factor」を 0.01 に設定
	const float scale_factor = 1.0f; // To change the units from centimeters to meters, set 'scale_factor' to 0.01.
#else
	const float scale_factor = 0.01f; // To change the units from centimeters to meters, set 'scale_factor' to 0.01.
#endif
	// 変換用
	DirectX::XMMATRIX C{ DirectX::XMLoadFloat4x4(&coordinate_system_transforms[0])* DirectX::XMMatrixScaling(scale_factor, scale_factor, scale_factor) };
	DirectX::XMMATRIX S{ DirectX::XMMatrixScaling(project->scale.x, project->scale.y, project->scale.z) };
	DirectX::XMMATRIX R{ DirectX::XMMatrixRotationRollPitchYaw(project->rotation.x, project->rotation.y, project->rotation.z) };
	DirectX::XMMATRIX T{ DirectX::XMMatrixTranslation(project->position.x, project->position.y, project->position.z) };
	// ワールド変換行列を作成
	DirectX::XMFLOAT4X4 world;
	DirectX::XMStoreFloat4x4(&world, C * S * R * T);


    BulletModel->render(immediate_context, world, project->material_color, nullptr, replaced_pixel_shader);
}

void GamePro_ProjectileStraightInputComponent::Update(GameObject* gameobj, float elapsedTime)
{
}

void GamePro_ProjectileStraightPhysicsComponent::Initialize(GameObject* gameobj)
{
}

void GamePro_ProjectileStraightPhysicsComponent::Update(GameObject* gameobj, float elapsedTime)
{
    GamePro_ProjectileStraight* project = dynamic_cast<GamePro_ProjectileStraight*> (gameobj);
    float speed = project->speed * elapsedTime;
    project->position.x += project->direction.x * speed;
    project->position.y += project->direction.y * speed;
    project->position.z += project->direction.z * speed;
}
