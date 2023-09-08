#pragma once

#include "../Lemur/Component/GameObject.h"
#include "../Lemur/Graphics/skinned_mesh.h"
#include "../Lemur/Graphics/Graphics.h"
#include "../Lemur/Resource/ResourceManager.h"

class Enemy :public GameObject
{
public:
    Enemy(InputComponent* input_,
        PhysicsComponent* physics_,
        GraphicsComponent* graphics_) :GameObject(input_, physics_, graphics_) {}
    float HitPoint = 0.0f;
    float Speed = 0.001f;
    float Atk;
    int EnemyType;
    static void DrawDebugGUI(GameObject* gameobj);
};

class EnemyInputComponent :public InputComponent
{
    void Initialize(GameObject* gameobj) override {}
    void Update(GameObject* gameobj, float elapsedTime) override;
};

class EnemyPhysicsComponent :public PhysicsComponent
{
    void Initialize(GameObject* gameobj) override;
    void Update(GameObject* gameobj, float elapsedTime) override;
};

class EnemyGraphicsComponent :public GraphicsComponent
{
    void Initialize(GameObject* gameobj) override;
    void Update(GameObject* gameobj) override;
    void Render(GameObject* gameobj, float elapsedTime, ID3D11PixelShader* replaced_pixel_shader) override;

private:
    std::shared_ptr<skinned_mesh> EnemyModel;

};