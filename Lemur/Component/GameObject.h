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
    GameObject(InputComponent* input_,
        PhysicsComponent* physics_,
        GraphicsComponent* graphics_)
        :input(input_),
        physics(physics_),
        graphics(graphics_)
    {}


    void Initialize()
    {
        input->Initialize(*this);
        physics->Initialize(*this);
        graphics->Initialize(*this);
    }

    void Update(float elapsedTime)
    {
        input->Update(*this, elapsedTime);
        physics->Update(*this, elapsedTime);
        graphics->Update(*this);
    }

    void Render(float elapsedTime)
    {
        graphics->Render(*this,elapsedTime, pixelShader);
    }

    void  ShadowRender(float elapsedTime)
    {
        graphics->ShadowRender(*this, elapsedTime);
    }

public:
    //DirectX::XMFLOAT3 translation{ 0, 0, 0 };
    //DirectX::XMFLOAT3 scaling{ 1, 1, 1 };
    //DirectX::XMFLOAT3 rotation{ 0, 0, 0 };
    //DirectX::XMFLOAT4 material_color{ 1, 1, 1, 1 };

    /// <summary>
    /// 自機
    /// </summary>
    DirectX::XMFLOAT3 translation{ 0, 0, 0 };
    DirectX::XMFLOAT3 scaling{ 3.0f, 3.0f, 3.0f };
    DirectX::XMFLOAT3 rotation{ 0, 0, 0 };
    DirectX::XMFLOAT4 material_color{ 1, 1, 1, 1 };

<<<<<<< HEAD
<<<<<<< HEAD
    DirectX::XMFLOAT3 player_translation{ 0, 0, 0 };
    DirectX::XMFLOAT3 player_scaling{ 1, 1, 1 };
    DirectX::XMFLOAT3 player_rotation{ 0, 0, 0 };
    DirectX::XMFLOAT4 player_material_color{ 1, 1, 1, 1 };
=======
=======
    float HitPoint = 0.0f;

    /// <summary>
    /// 弾
    /// </summary>

    //位置取得
    const DirectX::XMFLOAT3& GetPosition() const { return position; }
    //方向取得
    const DirectX::XMFLOAT3& GetDirection() const { return direction; }
    //スケール取得
    const DirectX::XMFLOAT3& GetScale() const { return scale; }

    DirectX::XMFLOAT3 position = { 0,0,0 };
    DirectX::XMFLOAT3 direction = { 0,0,1 };
    DirectX::XMFLOAT3 scale = { 1,1,1 };
    DirectX::XMFLOAT4X4 transform = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };

    float ProjectileSpeed = 0.0f;
    float ProjectileDamage = 0.0f;
    float ProjectileDamageSpeed = 0.0f;

    float ProjectileLevel = 0.0f;

    ///MAP
    DirectX::XMFLOAT3 map_translation{ 0, 0, 0 };
    DirectX::XMFLOAT3 map_scaling{ 30.0f, 30.0f, 30.0f };
    DirectX::XMFLOAT3 map_rotation{ 0, 0, 0 };
    DirectX::XMFLOAT4 map_material_color{ 1, 1, 1, 1 };

    /// <summary>
    /// マウス
    /// </summary>

    Mouse* mouse;

>>>>>>> d8f7efbbd44196f7b2e8607234d9fcb98c834910
    ID3D11PixelShader* pixelShader = nullptr;
>>>>>>> 3fc419464f32e32c77ebceb634ffa9eb188d8cc4

private:
    InputComponent* input;
    PhysicsComponent* physics;
    GraphicsComponent* graphics;
};