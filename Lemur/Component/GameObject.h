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

    virtual void Update(float elapsedTime)
    {
        input->Update(this, elapsedTime);
        physics->Update(this, elapsedTime);
        graphics->Update(this);
    }

    virtual void Render(float elapsedTime)
    {
        graphics->Render(this,elapsedTime, pixelShader);
    }

    void  ShadowRender(float elapsedTime)
    {
        graphics->ShadowRender(this, elapsedTime);
    }

public:

    DirectX::XMFLOAT3 position{ 0, 0, 0 };  // �ʒu
    DirectX::XMFLOAT3 scale{ 3.0f, 3.0f, 3.0f }; // �X�P�[��
    DirectX::XMFLOAT3 rotation{ 0, 0, 0 }; //�@��]
    DirectX::XMFLOAT4 material_color{ 1, 1, 1, 1 }; // �F

    DirectX::XMFLOAT3 direction = { 0,0,1 };// ����
    DirectX::XMFLOAT4X4 transform = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };// �s��

    Mouse* mouse;// �}�E�X

    ID3D11PixelShader* pixelShader = nullptr; // �V�F�[�_�[
    std::shared_ptr<skinned_mesh> stage_mesh;
    GameObject* player_;
protected:
    InputComponent* input;
    PhysicsComponent* physics;
    GraphicsComponent* graphics;

};