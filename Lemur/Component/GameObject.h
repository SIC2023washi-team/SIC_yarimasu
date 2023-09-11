#pragma once
#include "Component.h"
#include "./Lemur/Input/Mouse.h"
#include <d3d11.h>
#include <wrl.h>
#include <directxmath.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <fbxsdk.h>

class GameObject
{
public:
    GameObject() {};
    GameObject(InputComponent* input_,
        PhysicsComponent* physics_,
        GraphicsComponent* graphics_)
        :input(input_),
        physics(physics_),
        graphics(graphics_)
    {}


    virtual void Initialize()
    {
        input->Initialize(this);
        physics->Initialize(this);
        graphics->Initialize(this);
    }

    void Update(float elapsedTime)
    {
        input->Update(this, elapsedTime);
        physics->Update(this, elapsedTime);
        graphics->Update(this);
    }

    void Render(float elapsedTime)
    {
        graphics->Render(this,elapsedTime, pixelShader);
    }

    void  ShadowRender(float elapsedTime)
    {
        graphics->ShadowRender(this, elapsedTime);
    }

    void Delete()
    {
        delete input;
        delete physics;
        delete graphics;
    }


    // �����ړ��X�V����
    void UpdateHorizontalMove(float elapsedTime);

    // �������͍X�V����
    void UpdataHorizontalVelocity(float elapsedFrame);

    void AddImpulse(const DirectX::XMFLOAT3& impulse)
    {
        velocity.x += impulse.x;
        velocity.y += impulse.y;
        velocity.z += impulse.z;
    }


public:
    DirectX::XMFLOAT4X4 World;

    DirectX::XMFLOAT3 velocity{ 0, 0, 0 };  // ����
    DirectX::XMFLOAT3 position{ 0, 0, 0 };  // �ʒu
    DirectX::XMFLOAT3 scale{ 3.0f, 3.0f, 3.0f }; // �X�P�[��
    DirectX::XMFLOAT3 rotation{ 0, 0, 0 }; //�@��]
    DirectX::XMFLOAT4 material_color{ 1, 1, 1, 1 }; // �F

    DirectX::XMFLOAT3 direction = { 0,0,1 };// ����
    DirectX::XMFLOAT4X4 transform = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };// �s��

    float   maxMoveSpeed = 5.0f;
    float   moveVecX = 0.0f;
    float   moveVecZ = 0.0f;
    float   friction = 0.5f;
    float   acceleration = 1.0f;

    float radius = 1.0f;
    float height;

    Mouse* mouse;

    ID3D11PixelShader* pixelShader = nullptr;

    std::shared_ptr<skinned_mesh> stageModel;

    GameObject* player_;
    GameObject* enemy_;
    GameObject* projectile_;
    std::vector<GameObject*> enemyList_;

    //�G�l�~�[��auto�ňꊇ��������Ă��܂��̂ƈꊇ�����̓s����_rand�����܂��@�\���Ȃ��̂ŗp�ӂ������
    int NumDelivery[10];
    float NumFloatDelivery[10];
    
    std::vector<GameObject*> enemys_;

    bool Death = false;
private:
    InputComponent* input;
    PhysicsComponent* physics;
    GraphicsComponent* graphics;
};