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

public:

    DirectX::XMFLOAT3 position{ 0, 0, 0 };  // 位置
    DirectX::XMFLOAT3 scale{ 3.0f, 3.0f, 3.0f }; // スケール
    DirectX::XMFLOAT3 rotation{ 0, 0, 0 }; //　回転
    DirectX::XMFLOAT4 material_color{ 1, 1, 1, 1 }; // 色

    DirectX::XMFLOAT3 direction = { 0,0,1 };// 方向
    DirectX::XMFLOAT4X4 transform = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };// 行列


    //DirectX::XMFLOAT3 translation{ 0, 0, 0 };
    //DirectX::XMFLOAT3 scaling{ 1, 1, 1 };
    //DirectX::XMFLOAT3 rotation{ 0, 0, 0 };
    //DirectX::XMFLOAT4 material_color{ 1, 1, 1, 1 };

    ///// <summary>
    ///// 自機
    ///// </summary>
    //DirectX::XMFLOAT3 translation{ 0, 0, 0 };
    //DirectX::XMFLOAT3 scaling{ 3.0f, 3.0f, 3.0f };
    //DirectX::XMFLOAT3 rotation{ 0, 0, 0 };
    //DirectX::XMFLOAT4 material_color{ 1, 1, 1, 1 };

    //float HitPoint = 0.0f;

    ///// <summary>
    ///// 弾
    ///// </summary>

    ////位置取得
    //const DirectX::XMFLOAT3& GetPosition() const { return position; }
    ////方向取得
    //const DirectX::XMFLOAT3& GetDirection() const { return direction; }
    ////スケール取得
    //const DirectX::XMFLOAT3& GetScale() const { return scale; }

    //DirectX::XMFLOAT3 position = { 0,0,0 };
    //DirectX::XMFLOAT3 direction = { 0,0,1 };
    //DirectX::XMFLOAT3 scale = { 1,1,1 };
    //DirectX::XMFLOAT4X4 transform = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };

    /// <summary>
    /// マウス
    /// </summary>

    Mouse* mouse;

    ID3D11PixelShader* pixelShader = nullptr;

    std::shared_ptr<skinned_mesh> stageModel;

    GameObject* player_;
private:
    InputComponent* input;
    PhysicsComponent* physics;
    GraphicsComponent* graphics;
};