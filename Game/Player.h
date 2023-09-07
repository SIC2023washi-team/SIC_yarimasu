#pragma once
#include "../Lemur/Component/GameObject.h"
#include "../Lemur/Graphics/skinned_mesh.h"
#include "../Lemur/Graphics/Graphics.h"
#include "../Lemur/Resource/ResourceManager.h"
#include"../Lemur/Input/Input.h"


class Player :public GameObject
{
public:
    Player(InputComponent* input_,
        PhysicsComponent* physics_,
        GraphicsComponent* graphics_):GameObject(input_, physics_, graphics_){}
    float HitPoint = 0.0f;
};

class PlayerInputComponent :public InputComponent
{
    void Initialize(GameObject* gameobj) override {}
    void Update(GameObject* gameobj, float elapsedTime) override;
};

class PlayerPhysicsComponent :public PhysicsComponent
{
    void Initialize(GameObject* gameobj) override;
    void Update(GameObject* gameobj, float elapsedTime) override;
};

class PlayerGraphicsComponent :public GraphicsComponent
{
    void Initialize(GameObject* gameobj) override;
    void Update(GameObject* gameobj) override;
    void Render(GameObject* gameobj, float elapsedTime, ID3D11PixelShader* replaced_pixel_shader) override;

private:
    std::shared_ptr<skinned_mesh> PlayerModel;

};