#pragma once
#include "GameObject.h"
#include "Component.h"
#include "../Graphics/skinned_mesh.h"
#include "../Graphics/Graphics.h"
#include "../Resource/ResourceManager.h"
#include"../Input/Input.h"



class PlayerInputComponent :public InputComponent
{
    void Initialize(GameObject& gameobj) override {}
    void Update(GameObject& gameobj, float elapsedTime) override;
};

class PlayerPhysicsComponent :public PhysicsComponent
{
    void Initialize(GameObject& gameobj) override {}
    void Update(GameObject& gameobj, float elapsedTime) override {}
};

class PlayerGraphicsComponent :public GraphicsComponent
{
    void Initialize(GameObject& gameobj) override;
    void Update(GameObject& gameobj) override;
    void Render(GameObject& gameobj, float elapsedTime) override;

private:
    std::shared_ptr<skinned_mesh> PlayerModel;
};