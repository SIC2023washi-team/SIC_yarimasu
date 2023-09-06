#pragma once

#include <DirectXMath.h>
#include "../Graphics/skinned_mesh.h"
#include "GameObject.h"
#include "Component.h"

struct HitResult
{
    DirectX::XMFLOAT3 position = { 0,0,0 }; // レイとポリゴンの交点
    DirectX::XMFLOAT3 normal = { 0,0,0 };	// 衝突したポリゴンの法線ベクトル
    float distance = 0.0f;					// レイの始点から交点までの距離
    int materialIndex = -1;					// 衝突したポリゴンのマテリアル番号
    DirectX::XMFLOAT3 rotation = { 0,0,0 }; // 回転量
};

class CollisionPhysicsComponent :public PhysicsComponent
{
    void Initialize(GameObject& gameobj) override;
    void Update(GameObject& gameobj, float elapsedTime) override;
    
};