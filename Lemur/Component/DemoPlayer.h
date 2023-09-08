#pragma once
#include "GameObject.h"
#include "Component.h"
#include "../Graphics/skinned_mesh.h"
#include "../Graphics/Graphics.h"
#include "../Resource/ResourceManager.h"
#include"../Input/Input.h"

<<<<<<< HEAD
class DemoPlayer :public GameObject
{
    DemoPlayer(InputComponent* input_,
        PhysicsComponent* physics_,
        GraphicsComponent* graphics_) :GameObject(input_, physics_, graphics_) {}
};

=======
>>>>>>> washinao
class DemoPlayerInputComponent :public InputComponent
{
    void Initialize(GameObject* gameobj) override {}
    void Update(GameObject* gameobj, float elapsedTime) override;
};

class DemoPlayerPhysicsComponent :public PhysicsComponent
{
<<<<<<< HEAD
    void Initialize(GameObject* gameobj) override {}
    void Update(GameObject* gameobj, float elapsedTime) override {}
=======
    void Initialize(GameObject& gameobj) override {}
    void Update(GameObject& gameobj, float elapsedTime) override {}
>>>>>>> washinao
};

class DemoPlayerGraphicsComponent:public GraphicsComponent
{
<<<<<<< HEAD
    void Initialize(GameObject* gameobj) override;
    void Update(GameObject* gameobj) override;
    void Render(GameObject* gameobj, float elapsedTime,ID3D11PixelShader* replaced_pixel_shader) override;
    void ShadowRender(GameObject* gameobj, float elapsedTime)override;
=======
    void Initialize(GameObject& gameobj) override;
    void Update(GameObject& gameobj) override;
    void Render(GameObject& gameobj, float elapsedTime,ID3D11PixelShader* replaced_pixel_shader) override;
    void ShadowRender(GameObject& gameobj, float elapsedTime)override;
>>>>>>> washinao
private:
    std::shared_ptr<skinned_mesh> DemoPlayerModel;
};