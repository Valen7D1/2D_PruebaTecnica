#include "movement.h"

#include <string>
#include "collider.h"
#include "Entity.h"
#include "../World.h"
#include "../utils.h"


void PlayerMovement::Update(float DeltaTime)
{
    vec2 NewLocation = m_Data->Location + m_Direction * m_Speed * DeltaTime;
    printf("Input: (%f, %f)\n", m_Direction.x, m_Direction.y);
    const World* Manager = World::GetWorld();
    
    if (NewLocation.x - m_Data->Size.x/2 < 0.f) // collided with left wall
    {
        NewLocation.x = m_Data->Size.x/2;
    }
    if (NewLocation.x + m_Data->Size.x/2 > Manager->Width) // collided with right wall
    {
        NewLocation.x = Manager->Width - m_Data->Size.x/2;
    }
    
    m_Data->Location = NewLocation;
}


void EnemyMovement::Update(float DeltaTime)
{
    m_Data->Location = m_Data->Location + *m_ControllerInput * m_Speed * DeltaTime;
}


void ProjectileMovement::Update(float DeltaTime)
{
    m_Data->Location = m_Data->Location + m_Direction * m_Speed * DeltaTime;
    const World* Manager = World::GetWorld();
    
    if ( m_Data->Location.y + m_Data->Size.y < 0.f) // out of limits
    {
        m_Data->HasCollided = true;
    }
    if ( m_Data->Location.y - m_Data->Size.y > Manager->Height) // out of limits
    {
        m_Data->HasCollided = true;
    }
}
