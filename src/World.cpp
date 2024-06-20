#include "World.h"

#include "Components/Entity.h"
#include "Components/background.h"
#include "Components/controller.h"

World* World::instance = nullptr;


World* World::GetWorld() 
{   
    // if not created already then create it
    if (instance == nullptr)
    {
        instance = new World();
        instance->Init();
    }
    return instance;
}


void World::Update(float DeltaTime)
{
    lgfx_clearcolorbuffer(m_Red, m_Green, m_Blue);
    
    MyPlayer->Update(DeltaTime);
    EnemyController->Update(DeltaTime);

    // projectile update
    QueueNode<Barrier>* CurrentNode = Barriers->getHead();
    while (CurrentNode != nullptr)
    {
        QueueNode<Barrier>* NextNode = CurrentNode->next;
        if (CurrentNode->data->GetHealth() == 0) // projectile has collided so must be destroyed
        {
            delete CurrentNode->data;
            Barriers->erase(CurrentNode);
            // here create entity of type explosion
        }
        else
        {
            CurrentNode->data->Update(DeltaTime);
        }
        CurrentNode = NextNode;
    }
}


void World::Init()
{
    // place holder load of level 1
    MyPlayer = new Player();
    EnemyController = new Controller();
    Barriers = new Queue<Barrier>();

    // enemies creation
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
            NewEnemy = new Enemy(EnemyController->GetInputVector(),EnemyController,
                vec2(startX + xOffset * static_cast<float>(col),startY + yOffset * static_cast<float>(row)), NewEnemy);
        }
        NewEnemy->SetCanShoot(true);
    }
    
    // static entities creation (super placeholder)
    Barriers->enqueue(new Barrier(vec2(100.f, 625.f), vec2(100, 20)));
    Barriers->enqueue(new Barrier(vec2(300.f, 625.f), vec2(100, 20)));
    Barriers->enqueue(new Barrier(vec2(500.f, 625.f), vec2(100, 20)));
    Barriers->enqueue(new Barrier(vec2(700.f, 625.f), vec2(100, 20)));
}


void World::EndGame(bool _hasWon)
{
    
}
