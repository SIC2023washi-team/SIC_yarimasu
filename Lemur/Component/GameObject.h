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
<<<<<<< HEAD
        graphics->Render(this,elapsedTime, pixelShader);
=======
        graphics->Render(*this,elapsedTime, pixelShader);
>>>>>>> washinao
    }

    void  ShadowRender(float elapsedTime)
    {
<<<<<<< HEAD
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

    GameObject* player_;
protected:
=======
        graphics->ShadowRender(*this, elapsedTime);
    }

public:
    //DirectX::XMFLOAT3 translation{ 0, 0, 0 };
    //DirectX::XMFLOAT3 scaling{ 1, 1, 1 };
    //DirectX::XMFLOAT3 rotation{ 0, 0, 0 };
    //DirectX::XMFLOAT4 material_color{ 1, 1, 1, 1 };

    /// <summary>
    /// ���@
    /// </summary>
    DirectX::XMFLOAT3 translation{ 0, 0, 0 };
    DirectX::XMFLOAT3 scaling{ 3.0f, 3.0f, 3.0f };
    DirectX::XMFLOAT3 rotation{ 0, 0, 0 };
    DirectX::XMFLOAT4 material_color{ 1, 1, 1, 1 };

    float HitPoint = 0.0f;

    /// <summary>
    /// �e
    /// </summary>

    //�ʒu�擾
    const DirectX::XMFLOAT3& GetPosition() const { return position; }
    //�����擾
    const DirectX::XMFLOAT3& GetDirection() const { return direction; }
    //�X�P�[���擾
    const DirectX::XMFLOAT3& GetScale() const { return scale; }

    DirectX::XMFLOAT3 position = { 0,0,0 };
    DirectX::XMFLOAT3 direction = { 0,0,1 };
    DirectX::XMFLOAT3 scale = { 1,1,1 };
    DirectX::XMFLOAT4X4 transform = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };

    float ProjectileSpeed = 0.0f;
    float ProjectileDamage = 0.0f;
    float ProjectileDamageSpeed = 0.0f;

    float ProjectileLevel = 0.0f;

    /// <summary>
    /// �}�E�X
    /// </summary>

    Mouse* mouse;

    ID3D11PixelShader* pixelShader = nullptr;

    std::shared_ptr<skinned_mesh> stage;
private:
>>>>>>> washinao
    InputComponent* input;
    PhysicsComponent* physics;
    GraphicsComponent* graphics;

};