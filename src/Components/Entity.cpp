#include "Entity.h"

#include "collider.h"
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


#pragma region Projectile

Projectile::Projectile(vec2 _location)
{
    m_Data = new EData(_location, vec2(50.f, 50.f));
    ltex_t* ProjectileTex = Sprite::loadImage("Data/circle.png");
    m_Sprite = new Sprite(ProjectileTex, m_Data, 1, 1, 1, Color::White());
    m_Collider = Collider::CreateCollider(COLLISION_CIRCLE, ProjectileTex, m_Data);
    m_Movement = new ProjectileMovement(this, m_Data);
}

Projectile::~Projectile()
{
    delete m_Movement;
}

void Projectile::Update(float DeltaTime)
{
    m_Movement->Update(DeltaTime);
    m_Collider->CheckCollision();
    m_Sprite->update(DeltaTime);
}

#pragma endregion


#pragma region Player

Player::Player()
{
    m_Data = new EData(vec2(400.f, 400.f), vec2(100.f, 100.f));
    ltex_t* PlayerTex = Sprite::loadImage("Data/rect.png");
    m_Sprite = new Sprite(PlayerTex, m_Data, 1, 1, 1, Color::White());
    m_Collider = Collider::CreateCollider(COLLISION_RECT, PlayerTex, m_Data);
    m_Movement = new DirectionalMovement(this, m_Data);
    m_ProjectileQueue = new Queue();
}

Player::~Player()
{
    delete m_Movement;
}

void Player::Update(float DeltaTime)
{
    m_Movement->Update(DeltaTime); // move to the proposed new location
    m_Collider->CheckCollision(); // if location needs reset
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
            
            m_ProjectileQueue->enqueue(new Projectile(StartingLocation));
            m_ProjectileTimer = m_TimeInBetweenShots;
        }
    }

    // projectile queue for optimal performance
    QueueNode* CurrentNode = m_ProjectileQueue->getHead();
    while (CurrentNode != nullptr)
    {
        QueueNode* NextNode = CurrentNode->next;
        if (CurrentNode->data) // if that projectile hasn't been destroyed
        {
            CurrentNode->data->Update(DeltaTime);
        }
        else
        {
            m_ProjectileQueue->erase(CurrentNode);
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
