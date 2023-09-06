#pragma once
#include "GameObject.h"
#include "Component.h"
#include "../Graphics/skinned_mesh.h"
#include "../Graphics/Graphics.h"
#include "../Resource/ResourceManager.h"
#include"../Input/Input.h"
#include <Lemur/Component/Collision.h>



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
    void Render(GameObject& gameobj, float elapsedTime) override;

private:
    std::shared_ptr<skinned_mesh> stage;

};