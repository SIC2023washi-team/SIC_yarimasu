#pragma once

#include "GameObject.h"
#include "Component.h"
#include "../Graphics/skinned_mesh.h"
#include "../Graphics/Graphics.h"
#include "../Resource/ResourceManager.h"
#include"../Input/Input.h"

//’e
//class DemoProjectileComponent :public InputComponent
//{
//    void Initialize(GameObject& gameobj) override {}
//    void Update(GameObject& gameobj, float elapsedTime) override;
//};

class ProjectilePhysicsComponent :public PhysicsComponent
{
    void Initialize(GameObject& gameobj) override;
    void Update(GameObject& gameobj, float elapsedTime) override;
};

class ProjectileGraphicsComponent :public GraphicsComponent
{
    void Initialize(GameObject& gameobj) override;
    void Update(GameObject& gameobj) override;
    void Render(GameObject& gameobj, float elapsedTime) override;

private:
    std::shared_ptr<skinned_mesh> DemoPlayerModel; ///ƒ‚ƒfƒ‹‘Ò‚¿
};