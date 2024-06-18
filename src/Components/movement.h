#pragma once

#include <cstdio>

#include "../Vec2.h"

class Entity;

struct EData;

class Movement
{
public:
    Movement(Entity* _entity,  EData* _data, vec2 _baseSpeed = vec2(100.f, 100.f)) :
    m_Entity(_entity), m_Data(_data), m_Speed(_baseSpeed) {}
    
    virtual ~Movement() = default;    
    virtual void Update(float DeltaTime) = 0;

    void SetSpeed(vec2 _newSpeed) { m_Speed = _newSpeed; }
    void SetDirection(vec2 _newDir) { m_Direction = _newDir; }

    vec2 GetSpeed() { return m_Speed; }
    
protected:
    Entity* m_Entity = nullptr;
    EData* m_Data = nullptr;

    vec2 m_Speed = vec2(100.f, 100.f);
    vec2 m_Direction = vec2();
};


class DirectionalMovement : public Movement
{
public:
    DirectionalMovement(Entity* _entity,  EData* _data, vec2 _baseSpeed = vec2(100.f, 100.f)) : Movement(_entity, _data, _baseSpeed){}
    void Update(float DeltaTime) override;
};

class ProjectileMovement : public Movement
{
public:
    ProjectileMovement(Entity* _entity,  EData* _data, vec2 _baseSpeed = vec2(100.f, 100.f)) : Movement(_entity, _data, _baseSpeed){}
    void Update(float DeltaTime) override;
};
