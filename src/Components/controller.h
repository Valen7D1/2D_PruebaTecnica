#pragma once

#include "../MyQueue.h"
#include "../Vec2.h"

class Enemy;

class Controller
{
public:
    Controller();
    ~Controller();

    void Update(float DeltaTime);
    
    Queue* GetEnemies() const { return m_Entities; }
    void AddEnemy(Entity* _newEnemy) { m_Entities->enqueue(_newEnemy); }

private:
    Queue* m_Entities;
    vec2* m_InputVector;

    // defaul variables for controller movement input
    vec2 m_Input =vec2(1.f, 4.f);

    float m_XTime = 5.f;
    float m_YTime = 1.f;

    float m_MovementTimer = 1.f;
    bool m_Direction = false; // false is on X axis, true is on Y axis
    bool m_XDirection = false; // false is -x true is +x

};