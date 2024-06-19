#include "controller.h"

#include "Entity.h"


Controller::Controller()
{
    m_Entities = new Queue();
    m_InputVector = new vec2(0.f, 1.f);
    
    AddEnemy(new Enemy(m_InputVector, vec2(250.f, 50.f)));
    AddEnemy(new Enemy(m_InputVector, vec2(350.f, 50.f)));
    AddEnemy(new Enemy(m_InputVector, vec2(450.f, 50.f)));
    AddEnemy(new Enemy(m_InputVector, vec2(550.f, 50.f)));
    
    AddEnemy(new Enemy(m_InputVector, vec2(250.f, 150.f)));
    AddEnemy(new Enemy(m_InputVector, vec2(350.f, 150.f)));
    AddEnemy(new Enemy(m_InputVector, vec2(450.f, 150.f)));
    AddEnemy(new Enemy(m_InputVector, vec2(550.f, 150.f)));
    
    AddEnemy(new Enemy(m_InputVector, vec2(250.f, 250.f)));
    AddEnemy(new Enemy(m_InputVector, vec2(350.f, 250.f)));
    AddEnemy(new Enemy(m_InputVector, vec2(450.f, 250.f)));
    AddEnemy(new Enemy(m_InputVector, vec2(550.f, 250.f)));
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
    
    
    // enemies update
    QueueNode* CurrentNode = m_Entities->getHead();
    while (CurrentNode != nullptr)
    {
        QueueNode* NextNode = CurrentNode->next;
        if (CurrentNode->data->HasCollided()) // projectile has collided so must be destroyed
        {
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
