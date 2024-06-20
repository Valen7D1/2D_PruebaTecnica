#include "Entity.h"

#include "collider.h"
#include "controller.h"
#include "movement.h"
#include "Sprite.h"
#include "../World.h"
#include <random>


float GenerateRandomFloat(float min, float max) {
    std::random_device rd;  // Seed generator
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

Entity::~Entity()
{
    delete m_Sprite;
    delete m_Data;
    delete m_Collider;
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
    m_Data = new EData(_location, vec2(25.f, 50.f));
    m_Sprite = new Sprite(World::GetWorld()->ProjectileTex, m_Data, 1, 1, 1, Color::White());
    m_Collider = Collider::CreateCollider(COLLISION_CIRCLE, World::GetWorld()->ProjectileTex, m_Data);
    m_Movement = new ProjectileMovement(this, m_Data, _direction);
}

Projectile::~Projectile()
{
    delete m_Movement;
}

void Projectile::Update(float DeltaTime)
{
    World* Manager = World::GetWorld();
    Queue<Enemy>* EnemyQueue = Manager->EnemyController->GetEnemies();
    
    // collision manager
    QueueNode<Enemy>* CurrentNode = EnemyQueue->getHead();
    while (CurrentNode != nullptr)
    {
        QueueNode<Enemy>* NextNode = CurrentNode->next;
        if (!CurrentNode->data->HasCollided()) // if enemy hasn't already collided with smth
        {
            m_Collider->collides(CurrentNode->data->GetCollider());
        }
        CurrentNode = NextNode;
    }

    // check also collision with player
    m_Collider->collides(Manager->MyPlayer->GetCollider());
    m_Movement->Update(DeltaTime);
    m_Sprite->update(DeltaTime);
}

#pragma endregion


#pragma region Player

Player::Player()
{
    m_Data = new EData(vec2(400.f, 750.f), vec2(60.f, 60.f));
    m_Sprite = new Sprite(World::GetWorld()->PlayerTex, m_Data, 1, 1, 1, Color::White());
    m_Collider = Collider::CreateCollider(COLLISION_RECT, World::GetWorld()->PlayerTex, m_Data);
    m_Movement = new PlayerMovement(this, m_Data);
    m_Projectiles = new Queue<Projectile>();
}

Player::~Player()
{
    delete m_Movement;
    delete m_Projectiles;
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
            
            m_Projectiles->enqueue(new Projectile(StartingLocation, vec2(0, -1.f)));
            m_ProjectileTimer = m_TimeInBetweenShots;
        }
    }

    // projectile queue for optimal performance
    QueueNode<Projectile>* CurrentNode = m_Projectiles->getHead();
    while (CurrentNode != nullptr)
    {
        QueueNode<Projectile>* NextNode = CurrentNode->next;
        if (CurrentNode->data->HasCollided()) // projectile has collided so must be destroyed
        {
            delete CurrentNode->data;
            m_Projectiles->erase(CurrentNode);
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

Enemy::Enemy(vec2* _inputVector, Controller* _owner,vec2 _location, Enemy* _nextInLine, bool _canShoot, vec2 _size)
{
    m_Owner =_owner;
    m_Owner->AddEnemy(this);
    
    m_Data = new EData(_location, _size);
    m_Sprite = new Sprite(World::GetWorld()->EnemyTex, m_Data, 1, 1, 1, Color::White());
    m_Collider = Collider::CreateCollider(COLLISION_RECT, World::GetWorld()->EnemyTex, m_Data);
    m_Movement = new EnemyMovement(this, m_Data, _inputVector);

    m_CanShoot = _canShoot;
    NextInLine = _nextInLine;
    m_ShootTimer = GenerateRandomFloat(3.f, 10.f);
}

Enemy::~Enemy()
{
    delete m_Movement;
}

void Enemy::Update(float DeltaTime)
{
    if (m_CanShoot)
    {
        m_ShootTimer -= DeltaTime;
        if (m_ShootTimer <= 0.f)
        {
            vec2 StartingLocation = m_Data->Location;
            StartingLocation.y += m_Data->Size.y;
            m_Owner->AddProjectile(new Projectile(StartingLocation, vec2(0, 1.f)));
            m_ShootTimer = GenerateRandomFloat(6.f, 10.f);
        }
        
    }
    
    m_Sprite->update(DeltaTime);
    m_Movement->Update(DeltaTime);
}

#pragma endregion


#pragma region Barrier

Barrier::Barrier(vec2 _location, vec2 _size)
{
    m_Data = new EData(_location, _size);
    ltex_t* StaticTex = Sprite::loadImage("data/rect.png");
    m_Sprite = new Sprite(StaticTex, m_Data, 1, 1, 1, Color::Green());
    m_Collider = Collider::CreateCollider(COLLISION_RECT, StaticTex, m_Data);
    
    VisualHealth.push_back(Color::Red());
    VisualHealth.push_back(Color::Orange());
    VisualHealth.push_back(Color::Yellow());

}

void Barrier::Update(float DeltaTime)
{
    World* Manager = World::GetWorld();

    // player projectiles dont do dmg but get destroyed
    QueueNode<Projectile>* CurrentNode = Manager->MyPlayer->GetProjectiles()->getHead();
    while (CurrentNode != nullptr)
    {
        QueueNode<Projectile>* NextNode = CurrentNode->next;
        if (!CurrentNode->data->HasCollided())
        {
            m_Collider->collides(CurrentNode->data->GetCollider());
        }
        CurrentNode = NextNode;
    }
    m_Data->HasCollided = false; // reset has collided just in case

    
    // check collisions with enemy projectiles
    CurrentNode = Manager->EnemyController->GetProjectiles()->getHead();
    while (CurrentNode != nullptr)
    {
        QueueNode<Projectile>* NextNode = CurrentNode->next;
        if (!CurrentNode->data->HasCollided())
        {
            m_Collider->collides(CurrentNode->data->GetCollider());
        }
        CurrentNode = NextNode;
    }
    
    if (m_Data->HasCollided)
    {
        --m_Health;
        m_Data->HasCollided = false;

        if (m_Health > 0)
        {
            m_Sprite->setColor(VisualHealth[m_Health-1]);
        }
    }
    m_Sprite->update(DeltaTime);
}

#pragma endregion