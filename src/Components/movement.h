#pragma once

#include <cstdio>

#include "../Vec2.h"

class Entity;

struct EData;

class Movement
{
public:
    Movement(Entity* _entity,  EData* _data, float _baseSpeed = 100.f) :
    m_Entity(_entity), m_Data(_data), m_Speed(_baseSpeed) {}
    
    virtual ~Movement() = default;    
    virtual void Update(float DeltaTime) = 0;

    void SetSpeed(float _newSpeed) { m_Speed = _newSpeed; }
    void SetDirection(vec2 _newDir) { m_Direction = _newDir; }

    float GetSpeed() { return m_Speed; }
    
protected:
    Entity* m_Entity = nullptr;
    EData* m_Data = nullptr;

    float m_Speed;
    vec2 m_Direction = vec2();
};


class PlayerMovement : public Movement
{
public:
    PlayerMovement(Entity* _entity,  EData* _data, float _baseSpeed = 200.f) : Movement(_entity, _data, _baseSpeed){}
    void Update(float DeltaTime) override;
};

class EnemyMovement : public Movement
{
public:
    EnemyMovement(Entity* _entity,  EData* _data, vec2* _controllerInput, float _baseSpeed = 20.f) : Movement(_entity, _data, _baseSpeed), m_ControllerInput(_controllerInput){}
    void Update(float DeltaTime) override;

private:
    vec2* m_ControllerInput;
};


class ProjectileMovement : public Movement
{
public:
    ProjectileMovement(Entity* _entity,  EData* _data, vec2 _direction,float _baseSpeed = 400.f) : Movement(_entity, _data, _baseSpeed){ m_Direction =  _direction; }
    void Update(float DeltaTime) override;
};
