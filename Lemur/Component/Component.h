#pragma once
#include "GameObject.h"
#include "misc.h"
#include "../Graphics/skinned_mesh.h"
#include "../Graphics/shader.h"
#include "../Graphics/texture.h"
#include <filesystem>
#include <sstream>
#include <functional>
<<<<<<< HEAD

#include <fstream>

=======
>>>>>>> washinao

#include <fstream>
class GameObject;

class Compornent
{
};

// �C���v�b�g�p���N���X
class InputComponent :public Compornent
{
public:
    virtual ~InputComponent() {}
    virtual void Initialize(GameObject* gameobj) = 0;
    virtual void Update(GameObject* gameobj, float elapsedTime) = 0;
};

// �O���t�B�b�N�p���N���X
class GraphicsComponent :public Compornent
{
public:
    virtual ~GraphicsComponent() {}
<<<<<<< HEAD
    virtual void Initialize(GameObject* gameobj) = 0;
    virtual void Update(GameObject* gameobj) = 0;
    virtual void Render(GameObject* gameobj, float elapsedTime, ID3D11PixelShader* replaced_pixel_shader) = 0;
    virtual void ShadowRender(GameObject* gameobj, float elapsedTime) {};
=======
    virtual void Initialize(GameObject& gameobj) = 0;
    virtual void Update(GameObject& gameobj) = 0;
    virtual void Render(GameObject& gameobj, float elapsedTime, ID3D11PixelShader* replaced_pixel_shader) = 0;
    virtual void ShadowRender(GameObject& gameobj, float elapsedTime) {};
>>>>>>> washinao
};

// �����p���N���X
class PhysicsComponent :public Compornent
{
public:
    virtual ~PhysicsComponent() {}
    virtual void Initialize(GameObject* gameobj) = 0;
    virtual void Update(GameObject* gameobj, float elapsedTime) = 0;
};
