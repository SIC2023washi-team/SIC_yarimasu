#pragma once
#include "GameObject.h"

class GameObject;

// コンポーネント基底クラス
class Component
{
public:
    virtual ~Component() {}
};

// インプット用基底クラス
class InputComponent 
{
public:
    virtual ~InputComponent() {}
    virtual void Initialize(GameObject& gameobj) = 0;
    virtual void Update(GameObject& gameobj, float elapsedTime) = 0;
};

// グラフィック用基底クラス
class GraphicsComponent 
{
public:
    virtual ~GraphicsComponent() {}
    virtual void Initialize(GameObject& gameobj) = 0;
    virtual void Update(GameObject& gameobj) = 0;
    virtual void Render(GameObject& gameobj, float elapsedTime) = 0;
};

// 物理用基底クラス
class PhysicsComponent 
{
public:
    virtual ~PhysicsComponent() {}
    virtual void Initialize(GameObject& gameobj) = 0;
    virtual void Update(GameObject& gameobj, float elapsedTime) = 0;
};
