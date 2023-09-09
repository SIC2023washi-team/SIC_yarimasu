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
public:
    DirectX::XMFLOAT4X4 World;

    DirectX::XMFLOAT3 position{ 0, 0, 0 };  // 位置
    DirectX::XMFLOAT3 scale{ 3.0f, 3.0f, 3.0f }; // スケール
    DirectX::XMFLOAT3 rotation{ 0, 0, 0 }; //　回転
    DirectX::XMFLOAT4 material_color{ 1, 1, 1, 1 }; // 色

    DirectX::XMFLOAT3 direction = { 0,0,1 };// 方向
    DirectX::XMFLOAT4X4 transform = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };// 行列

    float radius = 0;

    Mouse* mouse;

    ID3D11PixelShader* pixelShader = nullptr;

    std::shared_ptr<skinned_mesh> stageModel;

    GameObject* player_;
    GameObject* enemy_;

    std::vector<GameObject*> enemys_;

    bool Death = false;
private:
    InputComponent* input;
    PhysicsComponent* physics;
    GraphicsComponent* graphics;
};