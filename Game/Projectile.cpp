#include "Projectile.h"
#include "Mouse.h"
#include "Lemur/Graphics/Camera.h"

<<<<<<< HEAD
void ProjectilePhysicsComponent::Initialize(GameObject* gameobj)
=======
void ProjectilePhysicsComponent::Initialize(GameObject& gameobj)
>>>>>>> washinao
{

}

<<<<<<< HEAD
void ProjectilePhysicsComponent::Update(GameObject* gameobj, float elapsedTime)
{
	Projectile* prijectile = dynamic_cast<Projectile*> (gameobj);

	///‰¼‰ñ“]s—ñ
	prijectile->transform._11 = prijectile->scale.x;
	prijectile->transform._12 = 0.0f;
	prijectile->transform._13 = 0.0f;
	prijectile->transform._14 = 0.0f;
	prijectile->transform._21 = 0.0f;
	prijectile->transform._22 = prijectile->scale.y;
	prijectile->transform._23 = 0.0f;
	prijectile->transform._24 = 0.0f;
	prijectile->transform._31 = 0.0f;
	prijectile->transform._32 = 0.0f;
	prijectile->transform._33 = prijectile->scale.z;
	prijectile->transform._34 = 0.0f;
	prijectile->transform._41 = prijectile->position.x;
	prijectile->transform._42 = prijectile->position.y;
	prijectile->transform._43 = prijectile->position.z;
	prijectile->transform._44 = 1.0f;
}

void ProjectileGraphicsComponent::Initialize(GameObject* gameobj)
=======
void ProjectilePhysicsComponent::Update(GameObject& gameobj, float elapsedTime)
{
	///‰¼‰ñ“]s—ñ
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
>>>>>>> washinao
{

}

<<<<<<< HEAD
void ProjectileGraphicsComponent::Update(GameObject* gameobj)
=======
void ProjectileGraphicsComponent::Update(GameObject& gameobj)
>>>>>>> washinao
{

}

<<<<<<< HEAD
void ProjectileGraphicsComponent::Render(GameObject* gameobj, float elapsedTime, ID3D11PixelShader* replaced_pixel_shader)
=======
void ProjectileGraphicsComponent::Render(GameObject& gameobj, float elapsedTime, ID3D11PixelShader* replaced_pixel_shader)
>>>>>>> washinao
{

}