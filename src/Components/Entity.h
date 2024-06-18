#pragma once

#include <vector>
#include "../Vec2.h"
#include "../MyQueue.h"


enum CollisionType : int;
class Movement;
class Sprite;
class Collider;


struct EData;

class Entity
{
public:
    Entity() = default;
    virtual ~Entity();
    virtual void Update(float DeltaTime) = 0;

    Collider* GetCollider() const { return m_Collider; }
    EData* GetData() const { return m_Data; }
    
    void SetSprite(Sprite* _sprite);
    void SetCollider(Collider* _collider);

    
protected:
    Sprite* m_Sprite = nullptr;
    Collider* m_Collider = nullptr;
    EData* m_Data = nullptr;
};


class Projectile : public Entity
{
public:
    Projectile(vec2 _location);
    virtual ~Projectile() override;
    virtual void Update(float DeltaTime) override;
    
public:
    Movement* m_Movement = nullptr;

private:
    vec2 m_InputVector = vec2();
};


class Player : public Entity
{
public:
    Player();
    virtual ~Player() override;
    virtual void Update(float DeltaTime) override;
    
    void SetPlayerInput(vec2 _moveInput, bool _fireInput);
    
public:
    Movement* m_Movement = nullptr;

private:
    vec2 m_InputVector = vec2();
    Queue* m_ProjectileQueue;

    bool m_ProjectileInput = false;
    float m_ProjectileTimer = 0.f;
    float m_TimeInBetweenShots = 1.f;
};


class Enemy : public Entity
{
public:
    Enemy();
    virtual ~Enemy() override;
    virtual void Update(float DeltaTime) override;
    
    void SetEnemyDirection(vec2 _moveInput);
    
public:
    Movement* m_Movement = nullptr;

private:
    vec2 m_InputVector = vec2();
    
};