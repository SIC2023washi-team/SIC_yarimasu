#include "Projectile.h"
#include "Mouse.h"
#include "Lemur/Graphics/Camera.h"

void ProjectilePhysicsComponent::Initialize(GameObject& gameobj)
{

}

void ProjectilePhysicsComponent::Update(GameObject& gameobj, float elapsedTime)
{
	///âºâÒì]çsóÒ
	gameobj.transform._11 = gameobj.scale.x;
	gameobj.transform._12 = 0.0f;
	gameobj.transform._13 = 0.0f;
	gameobj.transform._14 = 0.0f;
	gameobj.transform._21 = 0.0f;
	gameobj.transform._22 = gameobj.scale.y;
	gameobj.transform._23 = 0.0f;
	gameobj.transform._24 = 0.0f;
	gameobj.transform._31 = 0.0f;
	gameobj.transform._32 = 0.0f;
	gameobj.transform._33 = gameobj.scale.z;
	gameobj.transform._34 = 0.0f;
	gameobj.transform._41 = gameobj.position.x;
	gameobj.transform._42 = gameobj.position.y;
	gameobj.transform._43 = gameobj.position.z;
	gameobj.transform._44 = 1.0f;
}

void ProjectileGraphicsComponent::Initialize(GameObject& gameobj)
{

}

void ProjectileGraphicsComponent::Update(GameObject& gameobj)
{

}

void ProjectileGraphicsComponent::Render(GameObject& gameobj, float elapsedTime, ID3D11PixelShader* replaced_pixel_shader)
{

}