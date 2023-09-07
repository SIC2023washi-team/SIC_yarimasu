#pragma once
#include "GameObject.h"
#include "Component.h"
#include "../Graphics/skinned_mesh.h"
#include "../Graphics/Graphics.h"
#include "../Resource/ResourceManager.h"
#include"../Input/Input.h"

class DemoPlayer :public GameObject
{

};

class DemoPlayerInputComponent :public InputComponent
{
    void Initialize(GameObject* gameobj) override {}
    void Update(GameObject* gameobj, float elapsedTime) override;
};

class DemoPlayerPhysicsComponent :public PhysicsComponent
{
    void Initialize(GameObject* gameobj) override {}
    void Update(GameObject* gameobj, float elapsedTime) override {}
};

class DemoPlayerGraphicsComponent:public GraphicsComponent
{
    void Initialize(GameObject* gameobj) override;
    void Update(GameObject* gameobj) override;
    void Render(GameObject* gameobj, float elapsedTime,ID3D11PixelShader* replaced_pixel_shader) override;
    void ShadowRender(GameObject* gameobj, float elapsedTime)override;
private:
    std::shared_ptr<skinned_mesh> DemoPlayerModel;
};