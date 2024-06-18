#include "movement.h"

#include <string>
#include "collider.h"
#include "Entity.h"
#include "../World.h"
#include "../utils.h"


void DirectionalMovement::Update(float DeltaTime)
{
    m_Data->Location = m_Data->Location + m_Direction * m_Speed * DeltaTime;
}

void ProjectileMovement::Update(float DeltaTime)
{
    m_Data->Location = m_Data->Location + vec2(0.f, -150.f) * DeltaTime;
}
