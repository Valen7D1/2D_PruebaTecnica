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
        instance->MyPlayer = new Player();
        instance->EnemyController = new Controller();
    }
    return instance;
}


void World::Update(float DeltaTime)
{
    lgfx_clearcolorbuffer(m_Red, m_Green, m_Blue);
    
    MyPlayer->Update(DeltaTime);
    EnemyController->Update(DeltaTime);
}