#include "GamePro_ProjectileStraight.h"

GamePro_ProjectileStraight::GamePro_ProjectileStraight()
{
    Lemur::Graphics::Graphics& graphics = Lemur::Graphics::Graphics::Instance();
    BulletModel = ResourceManager::Instance().LoadModelResource(graphics.GetDevice(), ".\\resources\\Model\\bot\\botcanon_player_v001.fbx");
}

GamePro_ProjectileStraight::~GamePro_ProjectileStraight()
{
    
}

void GamePro_ProjectileStraight::Update(float elapsedTime)
{
    float speed = this->speed * elapsedTime;
    position.x += direction.x * speed;
    position.y += direction.y * speed;
    position.z += direction.z * speed;

    //オブジェクト行列を更新
    UpdateTransform();

    //モデル行列更新
    BulletModel->UpdateTransform(transform);
}

void GamePro_ProjectileStraight::Render(ID3D11DeviceContext* dc, ID3D11PixelShader* replaced_pixel_shader)
{
    replaced_pixel_shader
}

void GamePro_ProjectileStraight::Launch(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& position)
{
    this->direction = direction;
    this->position = position;54
}
