#include "Enemy.h"

#define EnemyHitPoint 3.0f

//void EnemyInputComponent::Initialize(GameObject* gameobj)
//{
//
//}

void EnemyInputComponent::Update(GameObject* gameobj, float elapsedTime)
{

}

void EnemyPhysicsComponent::Initialize(GameObject* gameobj)
{
	Enemy* enemy = dynamic_cast<Enemy*> (gameobj);
	enemy->HitPoint = EnemyHitPoint;
}

void EnemyPhysicsComponent::Update(GameObject* gameobj, float elapsedTime)
{

}

void EnemyGraphicsComponent::Initialize(GameObject* gameobj)
{

}

void EnemyGraphicsComponent::Update(GameObject* gameobj)
{

}

void EnemyGraphicsComponent::Render(GameObject* gameobj, float elapsedTime, ID3D11PixelShader* replaced_pixel_shader)
{

}
