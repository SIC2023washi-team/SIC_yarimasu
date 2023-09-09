#pragma once

#include "../Lemur/Component/GameObject.h"
#include "../Lemur/Graphics/sprite.h"
#include "../Lemur/Graphics/Graphics.h"
#include "../Lemur/Resource/ResourceManager.h"
#include <sstream>

class Ui :public GameObject
{
public:
    Ui(InputComponent* input_,
        PhysicsComponent* physics_,
        GraphicsComponent* graphics_) :GameObject(input_, physics_, graphics_) {}


    DirectX::XMFLOAT2 pausePosition = { 1920,0 };

    enum ShopNumber {
        SpeedUp_A = 0,
        SpeedUp_P,
        Mine,
        Canon,
        PowerUp,
    };



};

class UiInputComponent :public InputComponent
{
    void Initialize(GameObject* gameobj) override {}
    void Update(GameObject* gameobj, float elapsedTime) override;
};

class UiPhysicsComponent :public PhysicsComponent
{
    void Initialize(GameObject* gameobj) override;
    void Update(GameObject* gameobj, float elapsedTime) override;
};

class UiGraphicsComponent :public GraphicsComponent
{
    void Initialize(GameObject* gameobj) override;
    void Update(GameObject* gameobj) override;
    void Render(GameObject* gameobj, float elapsedTime, ID3D11PixelShader* replaced_pixel_shader) override;

private:
    std::shared_ptr<sprite> pause;
    std::shared_ptr<sprite> option[5];
};