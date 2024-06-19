#include "Entity.h"

#include "collider.h"
#include "controller.h"
#include "movement.h"
#include "Sprite.h"
#include "../World.h"


Entity::~Entity()
{
     delete m_Sprite;
     delete m_Data;
}

void Entity::SetSprite(Sprite* _sprite)
{
    delete m_Sprite;
    m_Sprite = _sprite;
}

void Entity::SetCollider(Collider* _collider)
{
    delete m_Collider;
    m_Collider = _collider;
}

bool Entity::HasCollided() const
{
    return m_Data->HasCollided;
}


#pragma region Projectile

Projectile::Projectile(vec2 _location, vec2 _direction)
{
    m_Data = new EData(_location, vec2(25.f, 25.f));
    ltex_t* ProjectileTex = Sprite::loadImage("Data/circle.png");
    m_Sprite = new Sprite(ProjectileTex, m_Data, 1, 1, 1, Color::White());
    m_Collider = Collider::CreateCollider(COLLISION_CIRCLE, ProjectileTex, m_Data);
    m_Movement = new ProjectileMovement(this, m_Data, _direction);
}

Projectile::~Projectile()
{
    delete m_Movement;
}

void Projectile::Update(float DeltaTime)
{
    World* Manager = World::GetWorld();
    Queue* EnemyQueue = Manager->EnemyController->GetEnemies();
    
    QueueNode* CurrentNode = EnemyQueue->getHead();
    while (CurrentNode != nullptr)
    {
        QueueNode* NextNode = CurrentNode->next;
        if (!CurrentNode->data->HasCollided()) // if enemy hasn't already collided with smth
        {
            m_Collider->collides(CurrentNode->data->GetCollider());
        }
        CurrentNode = NextNode;
    }
    
    m_Movement->Update(DeltaTime);
    m_Sprite->update(DeltaTime);
}

#pragma endregion


#pragma region Player

Player::Player()
{
    m_Data = new EData(vec2(400.f, 650.f), vec2(100.f, 100.f));
    ltex_t* PlayerTex = Sprite::loadImage("Data/rect.png");
    m_Sprite = new Sprite(PlayerTex, m_Data, 1, 1, 1, Color::White());
    m_Collider = Collider::CreateCollider(COLLISION_RECT, PlayerTex, m_Data);
    m_Movement = new PlayerMovement(this, m_Data);
    m_ProjectileQueue = new Queue();
}

Player::~Player()
{
    delete m_Movement;
}

void Player::Update(float DeltaTime)
{
    m_Movement->Update(DeltaTime); // move to the proposed new location
    
    //m_Collider->CheckCollision();

    
    m_Sprite->update(DeltaTime);

    if (m_ProjectileTimer > 0.f)
    {
        m_ProjectileTimer -= DeltaTime;
    }
    else
    {
        if (m_ProjectileInput)
        {
            vec2 StartingLocation = m_Data->Location;
            StartingLocation.y -= m_Data->Size.y;
            
            m_ProjectileQueue->enqueue(new Projectile(StartingLocation, vec2(0, -1.f)));
            m_ProjectileTimer = m_TimeInBetweenShots;
        }
    }

    // projectile queue for optimal performance
    QueueNode* CurrentNode = m_ProjectileQueue->getHead();
    while (CurrentNode != nullptr)
    {
        QueueNode* NextNode = CurrentNode->next;
        if (CurrentNode->data->HasCollided()) // projectile has collided so must be destroyed
        {
            delete CurrentNode->data;
            m_ProjectileQueue->erase(CurrentNode);
            // here create entity of type explosion
        }
        else
        {
            CurrentNode->data->Update(DeltaTime);
        }
        CurrentNode = NextNode;
    }
}

void Player::SetPlayerInput(vec2 _newDir, bool _fireInput)
{
    m_Movement->SetDirection(_newDir);
    m_ProjectileInput = _fireInput;
}

#pragma endregion


#pragma region Enemy

Enemy::Enemy(vec2* _inputVector, vec2 _location, vec2 _size)
{
    m_Data = new EData(_location, _size);
    ltex_t* PlayerTex = Sprite::loadImage("Data/rect.png");
    m_Sprite = new Sprite(PlayerTex, m_Data, 1, 1, 1, Color::White());
    m_Collider = Collider::CreateCollider(COLLISION_RECT, PlayerTex, m_Data);
    m_Movement = new EnemyMovement(this, m_Data, _inputVector);
}

Enemy::~Enemy()
{
    delete m_Movement;
}

void Enemy::Update(float DeltaTime)
{
    m_Sprite->update(DeltaTime);
    m_Movement->Update(DeltaTime);
}


#pragma endregion