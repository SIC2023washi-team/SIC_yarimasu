#pragma once

#include "../Lemur/Graphics/skinned_mesh.h"
#include "GamePro_Projectile.h"

class GamePro_ProjectileStraight : public GamePro_Projectile
{
public:
    GamePro_ProjectileStraight();
    ~GamePro_ProjectileStraight() override;
    //更新処理
    void Update(float elapsedTime) override;
    //描画処理
    void Render(ID3D11DeviceContext* dc, ID3D11PixelShader* replaced_pixel_shader) override;
    //発射
    void Launch(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& position);

private:
    std::shared_ptr<skinned_mesh> BulletModel = nullptr;
    float speed = 1.0f;
};