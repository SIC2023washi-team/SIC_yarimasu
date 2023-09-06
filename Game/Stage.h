#pragma once
#include "../Lemur/Component/GameObject.h"
#include "../Lemur/Component/Component.h"
#include "../Lemur/Graphics/skinned_mesh.h"
#include "../Lemur/Graphics/Graphics.h"
#include "../Lemur/Resource/ResourceManager.h"
#include"../Lemur/Input/Input.h"
#include "../Lemur/Collision/Collision.h"



class StageInputComponent :public InputComponent
{
    void Initialize(GameObject& gameobj) override {}
    void Update(GameObject& gameobj, float elapsedTime) override;
};

class StagePhysicsComponent :public PhysicsComponent
{
    void Initialize(GameObject& gameobj) override;
    void Update(GameObject& gameobj, float elapsedTime) override;

};

class StageGraphicsComponent :public GraphicsComponent
{
    void Initialize(GameObject& gameobj) override;
    void Update(GameObject& gameobj) override;
    void Render(GameObject& gameobj, float elapsedTime,ID3D11PixelShader* replaced_pixel_shader) override;

private:
    std::shared_ptr<skinned_mesh> stage;

};