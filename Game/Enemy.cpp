#include "Enemy.h"
#include <imgui.h>
#include "./Lemur/Collision/Collision.h"
#include"./Lemur/Effekseer/EffekseerManager.h"
#include"./Lemur/Effekseer/Effect.h"

#define EnemyHitPoint 3.0f

//void EnemyInputComponent::Initialize(GameObject* gameobj)
//{
//
//}

void EnemyInputComponent::Update(GameObject* gameobj, float elapsedTime)
{

	Enemy* enemy = dynamic_cast<Enemy*> (gameobj);

	if (ImGui::TreeNode("TreeNode"))
	{
		ImGui::DragFloat3("pos", &enemy->position.x);
		ImGui::DragFloat3("rotate", &enemy->rotation.x);
		ImGui::DragFloat3("scale", &enemy->scale.x);
		ImGui::DragFloat("HP", &enemy->HP);
		ImGui::TreePop();
	}

	//if (ImGui::BeginMenu("menu"))
	//{
	//	ImGui::InputFloat3("Positon", &enemy->position.x);
	//	ImGui::EndMenu();
	//}

	//ImGui::Begin("Enemy"/*, nullptr, ImGuiWindowFlags_None)*/);

	//ImGui::InputFloat3("Positon", &enemy->position.x);

	//ImGui::DragFloat3("pos", &enemy->position.x);

	//ImGui::SliderFloat3("p", &enemy->position.x, 0.0f, 10.0f);

	//ImGui::End();
}

void EnemyPhysicsComponent::Initialize(GameObject* gameobj)
{
	Enemy* enemy = dynamic_cast<Enemy*> (gameobj);

	enemy->HP = EnemyHitPoint;
	enemy->scale.x = 16.f;
	enemy->scale.y = 16.f;
	enemy->scale.z = 16.f;
	enemy->position.y = 0.0f;
	enemy->radius = 1.0f;






	enemy->EnemyType = enemy->NumDelivery[0];
	switch (enemy->EnemyType)
	{
	default:
		break;
	case 0://小さいの
		enemy->Speed = 0.001f;
		enemy->AnimSpeed = 3.0f;
		break;
	case 1://中くらいの
		enemy->Speed = 0.0008f;
		enemy->AnimSpeed = 1.5f;
		break;
	case 2://大きいの
		enemy->Speed = 0.0005f;
		break;
	case 3://小さいしくそ早
		enemy->Speed = 0.003f;
		enemy->material_color = { 3.0f,1.5,1.5f,1.0f };
		enemy->AnimSpeed = 10.0f;
		break;
	}



	switch (enemy->NumDelivery[1])
	{
	case 0://上下からくる
		enemy->position.x = rand() % 16 - 8;
		enemy->position.z = 8 *(- 1 + (rand() % 2) * 2);
		break;
	case 1://左右からくる
		enemy->position.x = 8 * (-1 + (rand() % 2) * 2);
		enemy->position.z = rand() % 16 - 8;
		break;
	}

}

void EnemyPhysicsComponent::Update(GameObject* gameobj, float elapsedTime)
{

	Enemy* enemy = dynamic_cast<Enemy*> (gameobj);

	float px = (enemy->player_->position.x -enemy->position.x);
	float pz = (enemy->player_->position.z - enemy->position.z);
	DirectX::XMVECTOR vec_x  = DirectX::XMLoadFloat(&px);
	DirectX::XMVECTOR vec_z  = DirectX::XMLoadFloat(&pz);
	vec_x  = DirectX::XMVector3Normalize(vec_x);
	vec_z  = DirectX::XMVector3Normalize(vec_z);
	float floatX = DirectX::XMVectorGetX(vec_x);
	float floatZ = DirectX::XMVectorGetX(vec_z);
	enemy->position.x += floatX * enemy->Speed;
	//enemy->position.z += cos(enemy->rotation.y) * 0.001f;
	enemy->position.z += floatZ * enemy->Speed;
	
	///自機の回転
	//B-Aのベクトル
	DirectX::XMFLOAT3 RotationAngle = { enemy->player_->position.x - enemy->position.x,enemy->player_->position.y - enemy->position.y,enemy->player_->position.z - enemy->position.z };
	//正規化
	DirectX::XMVECTOR Normalizer = DirectX::XMVector3Normalize(XMLoadFloat3(&RotationAngle));

	enemy->rotation.y = atan2(RotationAngle.x, RotationAngle.z);

	if (enemy->HP <= 0)
	{
		enemy->clip_index = 1;
		enemy->AnimSpeed = 1.0f;
		// これで再生できる
		
	}
	else
	{
		enemy->clip_index = 0;
		float px = (enemy->player_->position.x - enemy->position.x);
		float pz = (enemy->player_->position.z - enemy->position.z);
		DirectX::XMVECTOR vec_x = DirectX::XMLoadFloat(&px);
		DirectX::XMVECTOR vec_z = DirectX::XMLoadFloat(&pz);
		vec_x = DirectX::XMVector3Normalize(vec_x);
		vec_z = DirectX::XMVector3Normalize(vec_z);
		float floatX = DirectX::XMVectorGetX(vec_x);
		float floatZ = DirectX::XMVectorGetX(vec_z);
		enemy->position.x += floatX * enemy->Speed;
		//enemy->position.z += cos(enemy->rotation.y) * 0.001f;
		enemy->position.z += floatZ * enemy->Speed;

		float cross = (enemy->position.z * enemy->player_->position.x) - (enemy->position.x * enemy->player_->position.z);
		if (cross < 0)
		{
			enemy->rotation.y += 0.01f;
		}
		else
		{
			enemy->rotation.y -= 0.01f;
		}

		///自機の回転
		//B-Aのベクトル
		DirectX::XMFLOAT3 RotationAngle = { enemy->player_->position.x - enemy->position.x,enemy->player_->position.y - enemy->position.y,enemy->player_->position.z - enemy->position.z };
		//正規化
		DirectX::XMVECTOR Normalizer = DirectX::XMVector3Normalize(XMLoadFloat3(&RotationAngle));

		enemy->rotation.y = atan2(RotationAngle.x, RotationAngle.z);
	}

	// 当たり判定
	DirectX::XMFLOAT3 p_p = enemy->position;
	float p_r = enemy->radius;
	DirectX::XMFLOAT3 e_p = enemy->player_->position;
	float e_r = enemy->player_->radius;

	if (Collision::IntersectSphereVsSphere(p_p, p_r, e_p, e_r))
	{
		enemy->Death = true;
	}

}

void EnemyGraphicsComponent::Initialize(GameObject* gameobj)
{
	Enemy* enemy = dynamic_cast<Enemy*> (gameobj);

	Lemur::Graphics::Graphics& graphics = Lemur::Graphics::Graphics::Instance();
	srand((unsigned int)time(NULL));

	switch (enemy->EnemyType)
	{
	default:
		break;
	case 0:
		EnemyModel = ResourceManager::Instance().LoadModelResource(graphics.GetDevice(), ".\\resources\\Model\\jank\\jank_low_v001.fbx");
		break;
	case 1:
		EnemyModel = ResourceManager::Instance().LoadModelResource(graphics.GetDevice(), ".\\resources\\Model\\jank\\jank_mid_v001.fbx");
		break;
	case 2:
		EnemyModel = ResourceManager::Instance().LoadModelResource(graphics.GetDevice(), ".\\resources\\Model\\jank\\jank_high_v002.fbx");
		break;
	case 3:
		EnemyModel = ResourceManager::Instance().LoadModelResource(graphics.GetDevice(), ".\\resources\\Model\\jank\\jank_low_v001.fbx");
		break;
	}

	explosionEffect = new Effect("/resources/Effects/explosion.efk");

}

void EnemyGraphicsComponent::Update(GameObject* gameobj)
{

}

void EnemyGraphicsComponent::Render(GameObject* gameobj, float elapsedTime, ID3D11PixelShader* replaced_pixel_shader)
{
	Enemy* enemy = dynamic_cast<Enemy*> (gameobj);

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
	DirectX::XMMATRIX S{ DirectX::XMMatrixScaling(enemy->scale.x, enemy->scale.y, enemy->scale.z) };
	DirectX::XMMATRIX R{ DirectX::XMMatrixRotationRollPitchYaw(enemy->rotation.x, enemy->rotation.y, enemy->rotation.z) };
	DirectX::XMMATRIX T{ DirectX::XMMatrixTranslation(enemy->position.x, enemy->position.y, enemy->position.z) };
	// ワールド変換行列を作成
	DirectX::XMFLOAT4X4 world;
	DirectX::XMStoreFloat4x4(&world, C * S * R * T);


	if (EnemyModel->animation_clips.size() > 0)
	{
		// アニメーション用
		int clip_index = enemy->clip_index;
		int frame_index = 0;
		static float animation_tick = 0;
#if 1
		animation& animation{ EnemyModel->animation_clips.at(clip_index) };
		frame_index = static_cast<int>(animation_tick * animation.sampling_rate);
		if (frame_index > animation.sequence.size() - 1)
		{
			frame_index = 0;
			animation_tick = 0;
		}
		else
		{
			animation_tick += elapsedTime*enemy->AnimSpeed;
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
		EnemyModel->render(immediate_context, world, enemy->material_color, &keyframe, replaced_pixel_shader);
	}
	else
	{
		EnemyModel->render(immediate_context, world, enemy->material_color, nullptr, replaced_pixel_shader);
	}

	DebugRenderer* debugRenderer = Lemur::Graphics::Graphics::Instance().GetDebugRenderer();

	//衝突判定用のデバッグ円柱を描画
	debugRenderer->DrawSphere(enemy->position, enemy->radius, DirectX::XMFLOAT4(0, 0, 0, 1));
	
	if (enemy->clip_index == 1)
	{
		
	}

}

