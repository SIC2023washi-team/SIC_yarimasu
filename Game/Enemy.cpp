#include "Enemy.h"
#include <imgui.h>

#define EnemyHitPoint 3.0f

//void EnemyInputComponent::Initialize(GameObject* gameobj)
//{
//
//}

void EnemyInputComponent::Update(GameObject* gameobj, float elapsedTime)
{
	//Enemy::DrawDebugGUI(gameobj);
	Enemy* enemy = dynamic_cast<Enemy*> (gameobj);

	if (ImGui::TreeNode("TreeNode"))
	{
		ImGui::DragFloat3("pos", &enemy->position.x);
		ImGui::DragFloat3("rotate", &enemy->rotation.x);
		ImGui::DragFloat3("scale", &enemy->scale.x);
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
	enemy->HitPoint = EnemyHitPoint;
	enemy->scale.x = 16.f;
	enemy->scale.y = 16.f;
	enemy->scale.z = 16.f;
}

void EnemyPhysicsComponent::Update(GameObject* gameobj, float elapsedTime)
{
	Enemy* enemy = dynamic_cast<Enemy*> (gameobj);
	//DirectX::XMFLOAT3 moveVec = GetMoveVec();

	enemy->position.x += sin(enemy->rotation.y) *0.001f;
	enemy->position.z += cos(enemy->rotation.y) * 0.001f;
}

void EnemyGraphicsComponent::Initialize(GameObject* gameobj)
{
	Lemur::Graphics::Graphics& graphics = Lemur::Graphics::Graphics::Instance();
	EnemyModel = ResourceManager::Instance().LoadModelResource(graphics.GetDevice(), ".\\resources\\Model\\jank\\jank_mid_v001.fbx");
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
		int clip_index = 0;
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
		EnemyModel->render(immediate_context, world, enemy->material_color, &keyframe, replaced_pixel_shader);
}
	else
	{
		EnemyModel->render(immediate_context, world, enemy->material_color, nullptr, replaced_pixel_shader);
	}

	
}

void Enemy::DrawDebugGUI(GameObject* gameobj)
{
	Enemy* enemy = dynamic_cast<Enemy*> (gameobj);

	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Enemy", nullptr, ImGuiWindowFlags_None))
	{
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::InputFloat3("Positon", &enemy->position.x);
		}

	}

}