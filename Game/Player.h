#pragma once
#include "../Lemur/Component/GameObject.h"
#include "../Lemur/Graphics/skinned_mesh.h"
#include "../Lemur/Graphics/Graphics.h"
#include "../Lemur/Resource/ResourceManager.h"
#include"../Lemur/Input/Input.h"


<<<<<<< HEAD
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
=======

class PlayerInputComponent :public InputComponent
{
    void Initialize(GameObject& gameobj) override {}
    void Update(GameObject& gameobj, float elapsedTime) override;
>>>>>>> washinao
};

class PlayerPhysicsComponent :public PhysicsComponent
{
<<<<<<< HEAD
    void Initialize(GameObject* gameobj) override;
    void Update(GameObject* gameobj, float elapsedTime) override;
=======
    void Initialize(GameObject& gameobj) override;
    void Update(GameObject& gameobj, float elapsedTime) override;
>>>>>>> washinao
};

class PlayerGraphicsComponent :public GraphicsComponent
{
<<<<<<< HEAD
    void Initialize(GameObject* gameobj) override;
    void Update(GameObject* gameobj) override;
    void Render(GameObject* gameobj, float elapsedTime, ID3D11PixelShader* replaced_pixel_shader) override;
=======
    void Initialize(GameObject& gameobj) override;
    void Update(GameObject& gameobj) override;
    void Render(GameObject& gameobj, float elapsedTime, ID3D11PixelShader* replaced_pixel_shader) override;
>>>>>>> washinao

private:
    std::shared_ptr<skinned_mesh> PlayerModel;

};