#pragma once

#include "../Lemur/Component/GameObject.h"
#include "../Lemur/Component/Component.h"
#include "../Lemur/Graphics/skinned_mesh.h"
#include "../Lemur/Graphics/Graphics.h"
#include "../Lemur/Resource/ResourceManager.h"
#include"../Lemur/Input/Input.h"

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
    void Render(GameObject& gameobj, float elapsedTime,ID3D11PixelShader* replaced_pixel_shader) override;

private:
    std::shared_ptr<skinned_mesh> DemoPlayerModel; ///ƒ‚ƒfƒ‹‘Ò‚¿
};