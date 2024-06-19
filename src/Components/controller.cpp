#include "controller.h"

#include "Entity.h"


Controller::Controller()
{
    m_Projectiles = new Queue<Projectile>();
    m_Entities = new Queue<Enemy>();
    m_InputVector = new vec2(0.f, 1.f);

    const int rows = 3;
    const int cols = 4;
    const float startX = 250.f;
    const float startY = 50.f;
    const float xOffset = 100.f;
    const float yOffset = 100.f;
    
    for (int col = 0; col < cols; ++col)
    {
        Enemy* NewEnemy = nullptr;
        for (int row = 0; row < rows; ++row)
        {
            NewEnemy = new Enemy(m_InputVector, vec2(startX + xOffset * static_cast<float>(col), startY + yOffset * static_cast<float>(row)), NewEnemy);
            AddEnemy(NewEnemy);
        }
        NewEnemy->SetCanShoot(true);
    }
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
    QueueNode<Enemy>* CurrentNode = m_Entities->getHead();
    while (CurrentNode != nullptr)
    {
        QueueNode<Enemy>* NextNode = CurrentNode->next;
        if (CurrentNode->data->HasCollided()) // projectile has collided so must be destroyed
        {
            if(CurrentNode->data->NextInLine)
            {
                CurrentNode->data->NextInLine->SetCanShoot(true);
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
