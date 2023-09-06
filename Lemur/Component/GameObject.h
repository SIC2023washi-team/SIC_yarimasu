#pragma once
#include "Component.h"
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
    DirectX::XMFLOAT3 translation{ 0, 0, 0 };
    DirectX::XMFLOAT3 scaling{ 3.0f, 3.0f, 3.0f };
    DirectX::XMFLOAT3 rotation{ 0, 0, 0 };
    DirectX::XMFLOAT4 material_color{ 1, 1, 1, 1 };

<<<<<<< HEAD
    DirectX::XMFLOAT3 player_translation{ 0, 0, 0 };
    DirectX::XMFLOAT3 player_scaling{ 1, 1, 1 };
    DirectX::XMFLOAT3 player_rotation{ 0, 0, 0 };
    DirectX::XMFLOAT4 player_material_color{ 1, 1, 1, 1 };
=======
    ID3D11PixelShader* pixelShader = nullptr;
>>>>>>> 3fc419464f32e32c77ebceb634ffa9eb188d8cc4

private:
    InputComponent* input;
    PhysicsComponent* physics;
    GraphicsComponent* graphics;
};