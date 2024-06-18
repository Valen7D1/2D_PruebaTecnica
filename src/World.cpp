#include "World.h"

#include "Components/camera.h"
#include "Components/Entity.h"
#include "Components/background.h"

World* World::instance = nullptr;


World* World::GetWorld() 
{   
    // if not created already then create it
    if (instance == nullptr)
    {
        instance = new World();
    }
    return instance;
}


void World::Update(float DeltaTime)
{

    lgfx_clearcolorbuffer(m_Red, m_Green, m_Blue);
    
    for (Entity* _entity : m_Entities)
    {
        _entity->Update(DeltaTime); 
    }
}


#pragma region Setters / Getters

void World::AddEntity(Entity* _entity)
{
    m_Entities.push_back(_entity);
}

void World::RemoveEntity(Entity* _entityToErase)
{
    auto const Iterator = std::find(m_Entities.begin(), m_Entities.end(), _entityToErase); 
    if (Iterator != m_Entities.end())
    { 
        m_Entities.erase(Iterator); 
    }
    delete _entityToErase;
}

#pragma endregion