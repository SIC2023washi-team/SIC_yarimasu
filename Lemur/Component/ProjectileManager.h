#pragma once

#include <vector>
#include "Projectile.h"

//弾マネージャー
class ProjectileManager
{
    ProjectileManager();
    ~ProjectileManager();

    //更新処理
    void Update(float elapsedTime);

    //描画処理
    void Render(ID3D11DeviceContext* dc);

    //デバックプリミティブ描画
    void DrawDebugPrimitive();

    //弾丸登録
    void Register(ProjectilePhysicsComponent* projectile);

    //弾丸全削除
    void Clear();

    //弾丸数取得
    int GetProjectileCount() const { return static_cast<int>(P_projectiles.size()); }

    //弾丸取得
    ProjectilePhysicsComponent* GetProjectile(int index) { return P_projectiles.at(index); }

private:
    std::vector<ProjectilePhysicsComponent*> P_projectiles;
    std::vector<ProjectileGraphicsComponent*> G_projectiles;
};

//class ProjectileManagerInputComponent :public InputComponent
//{
//    void Initialize(GameObject& gameobj) override {}
//    void Update(GameObject& gameobj, float elapsedTime) override;
//};
//
//class ProjectileManagerPhysicsComponent :public PhysicsComponent
//{
//    void Initialize(GameObject& gameobj) override;
//    void Update(GameObject& gameobj, float elapsedTime) override;
//};
//
//class ProjectileManagerGraphicsComponent :public GraphicsComponent
//{
//    void Initialize(GameObject& gameobj) override;
//    void Update(GameObject& gameobj) override;
//    void Render(GameObject& gameobj, float elapsedTime) override;
//
//private:
//    std::shared_ptr<skinned_mesh> DemoPlayerModel; ///モデル待ち
//};