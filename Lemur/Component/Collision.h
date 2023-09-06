#pragma once

#include <DirectXMath.h>
#include "../Graphics/skinned_mesh.h"
#include "GameObject.h"
#include "Component.h"

struct HitResult
{
    DirectX::XMFLOAT3 position = { 0,0,0 }; // ���C�ƃ|���S���̌�_
    DirectX::XMFLOAT3 normal = { 0,0,0 };	// �Փ˂����|���S���̖@���x�N�g��
    float distance = 0.0f;					// ���C�̎n�_�����_�܂ł̋���
    int materialIndex = -1;					// �Փ˂����|���S���̃}�e���A���ԍ�
    DirectX::XMFLOAT3 rotation = { 0,0,0 }; // ��]��
};

class CollisionPhysicsComponent :public PhysicsComponent
{
    void Initialize(GameObject& gameobj) override;
    void Update(GameObject& gameobj, float elapsedTime) override;
    
};