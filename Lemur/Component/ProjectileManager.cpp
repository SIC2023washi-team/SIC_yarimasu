#include "GameObject.h"
#include "ProjectileManager.h"
#include "Projectile.h"
#include "Mouse.h"
#include "Lemur/Graphics/Camera.h"

//void ProjectileManagerInputComponent::Initialize(GameObject& gameobj)
//{
//
//}
//
//void ProjectileManagerInputComponent::Update(GameObject& gameobj, float elapsedTime) 
//{
//
//}
//
//void ProjectileManagerPhysicsComponent::Initialize(GameObject& gameobj)
//{
//
//}
//
//void ProjectileManagerPhysicsComponent::Update(GameObject& gameobj, float elapsedTime)
//{
//    
//}
//
//void ProjectileManagerGraphicsComponent::Initialize(GameObject& gameobj)
//{
//
//}
//
//void ProjectileManagerGraphicsComponent::Update(GameObject& gameobj)
//{
//
//}
//
//void ProjectileManagerGraphicsComponent::Render(GameObject& gameobj, float elapsedTime)
//{
//    
//}

ProjectileManager::ProjectileManager()
{

}

ProjectileManager::~ProjectileManager()
{
    Clear();
}

//XVˆ—
void ProjectileManager::Update(float elapsedTime)
{
    for (ProjectilePhysicsComponent* projectile : P_projectiles)
    {
        //projectile->Update(elapsedTime);
    }
}

void ProjectileManager::Render(ID3D11DeviceContext* dc)
{
}

void ProjectileManager::DrawDebugPrimitive()
{
}

void ProjectileManager::Register(ProjectilePhysicsComponent* projectile)
{
}

void ProjectileManager::Clear()
{
}
