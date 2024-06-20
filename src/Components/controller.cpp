#include "controller.h"

#include "Entity.h"


Controller::Controller()
{
    m_Projectiles = new Queue<Projectile>();
    m_Entities = new Queue<Enemy>();
    m_InputVector = new vec2(0.f, 1.f);
}

Controller::~Controller()
{
    delete m_Entities;
    delete m_InputVector;
}

void Controller::Update(float DeltaTime)
{
    m_MovementTimer -= DeltaTime;
    if (m_MovementTimer <= 0.f)
    {
        if (m_Direction) {
            m_InputVector->x = 0.f;
            m_InputVector->y = 1.f;
            m_MovementTimer = 0.10f;
        } else {
            m_InputVector->x = m_XDirection ? -1.f : 1.f;
            m_InputVector->y = 0.f;
            m_MovementTimer = 5.f;
            m_XDirection = !m_XDirection;
        }

        m_Direction = !m_Direction;
        *m_InputVector = *m_InputVector * m_Input;
    }
    

    // projectile update
    QueueNode<Projectile>* CurrentProjectile = m_Projectiles->getHead();
    while (CurrentProjectile != nullptr)
    {
        QueueNode<Projectile>* NextProjectile = CurrentProjectile->next;
        if (CurrentProjectile->data->HasCollided()) // projectile has collided so must be destroyed
        {
            delete CurrentProjectile->data;
            m_Projectiles->erase(CurrentProjectile);
            // here create entity of type explosion
        }
        else
        {
            CurrentProjectile->data->Update(DeltaTime);
        }
        CurrentProjectile = NextProjectile;
    }
    
    // enemies update
    QueueNode<Enemy>* CurrentNode = m_Entities->getHead();
    while (CurrentNode != nullptr)
    {
        QueueNode<Enemy>* NextNode = CurrentNode->next;
        if (CurrentNode->data->HasCollided()) // projectile has collided so must be destroyed
        {
            if(CurrentNode->data->NextInLine)
            {
                CurrentNode->data->NextInLine->SetCanShoot(true); // set new shooter in line if possible
            }
          
            delete CurrentNode->data;
            m_Entities->erase(CurrentNode);
            // here create entity of type explosion
        }
        else
        {
            CurrentNode->data->Update(DeltaTime);
        }
        CurrentNode = NextNode;
    }
}
