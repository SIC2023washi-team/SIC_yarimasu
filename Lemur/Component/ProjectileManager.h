#pragma once

#include <vector>
#include "Projectile.h"

//�e�}�l�[�W���[
class ProjectileManager
{
    ProjectileManager();
    ~ProjectileManager();

    //�X�V����
    void Update(float elapsedTime);

    //�`�揈��
    void Render(ID3D11DeviceContext* dc);

    //�f�o�b�N�v���~�e�B�u�`��
    void DrawDebugPrimitive();

    //�e�ۓo�^
    void Register(ProjectilePhysicsComponent* projectile);

    //�e�ۑS�폜
    void Clear();

    //�e�ې��擾
    int GetProjectileCount() const { return static_cast<int>(P_projectiles.size()); }

    //�e�ێ擾
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
//    std::shared_ptr<skinned_mesh> DemoPlayerModel; ///���f���҂�
//};