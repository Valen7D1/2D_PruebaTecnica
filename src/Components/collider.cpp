#include "collider.h"

#include "Entity.h"
#include "../World.h"



Collider* Collider::CreateCollider(CollisionType _type, ltex_t* _tex, EData* _data)
{
    Collider * Temp = nullptr;
    switch (_type) {
    case COLLISION_NONE:
        return nullptr;
    case COLLISION_CIRCLE:
        return new CircleCollider(_data);
    case COLLISION_RECT:
        return new RectCollider(_data);
    case COLLISION_PIXELS:
        Temp = new PixelsCollider(_data, _tex);
        break;
    }
    return Temp;
}


#pragma region AllColliders


bool Collider::checkCircleCircle(const vec2& pos1, float radius1, const vec2& pos2, float radius2)
{
    return pos1.Distance(pos2) <= (radius1 + radius2);
}

bool Collider::checkCircleRect(const vec2& circlePos, float circleRadius, const vec2& rectPos, const vec2& rectSize)
{
    float const HalfRectWidth = rectSize.x / 2.0f;
    float const HalfRectHeight = rectSize.y / 2.0f;

    float const ClosestX = std::max(rectPos.x - HalfRectWidth, std::min(circlePos.x, rectPos.x + HalfRectWidth));
    float const ClosestY = std::max(rectPos.y - HalfRectHeight, std::min(circlePos.y, rectPos.y + HalfRectHeight));

    float const DistanceX = circlePos.x - ClosestX;
    float const DistanceY = circlePos.y - ClosestY;

    return (DistanceX * DistanceX + DistanceY * DistanceY) < (circleRadius * circleRadius);
}

bool Collider::checkRectRect(const vec2& rectPos1, const vec2& rectSize1, const vec2& rectPos2, const vec2& rectSize2)
{
    float const XDistance = abs(rectPos1.x - rectPos2.x);
    float const YDistance = abs(rectPos1.y - rectPos2.y);

    float const XMaxDistance = (rectSize1.x/2.f) + (rectSize2.x/2.f);
    float const YMaxDistance = (rectSize1.y/2.f) + (rectSize2.y/2.f);
    
    return (XDistance <= XMaxDistance && YDistance <= YMaxDistance);
}

bool Collider::checkCirclePixels(const vec2& circlePos, float circleRadius, const vec2& pixelsPos,
    const vec2& pixelsSize, const uint8_t* pixels)
{
    return false;
}

bool Collider::checkPixelsPixels(const vec2& pixelsPos1, const vec2& pixelsSize1, const uint8_t* pixels1,
    const vec2& pixelsPos2, const vec2& pixelsSize2, const uint8_t* pixels2)
{
    return false;
}

bool Collider::checkPixelsRect(const vec2& pixelsPos, const vec2& pixelsSize, const uint8_t* pixels,
    const vec2& rectPos, const vec2& rectSize)
{
    return false;
}

#pragma endregion


#pragma region CircleCollider

CircleCollider::CircleCollider(EData* _data) : Collider(_data, COLLISION_CIRCLE)
{
    float const Width = _data->Size.x;
    float const Height = _data->Size.y;
    
    m_Radius = (Height > Width) ? (Height / 2.0f) : (Width / 2.0f);
}

bool CircleCollider::collides(Collider* other)
{
    bool const HasCollided = other->collides(m_Data->Location, m_Radius);
    
    if(HasCollided)
    {
        this->SetHasCollided(HasCollided);
        other->SetHasCollided(HasCollided);
    }
    
    return HasCollided;
}

bool CircleCollider::collides(vec2& circlePos, float circleRadius)
{
    return checkCircleCircle(m_Data->Location, m_Radius, circlePos, circleRadius);
}

bool CircleCollider::collides(vec2& rectPos, vec2& rectSize)
{
    return checkCircleRect(m_Data->Location, m_Radius, rectPos, rectSize);
}

bool CircleCollider::collides(vec2& pixelsPos, vec2& pixelsSize, uint8_t* pixels)
{
    return checkCirclePixels(m_Data->Location, m_Radius, pixelsPos, pixelsSize, pixels);
}

#pragma endregion


#pragma region RectangleCollider

RectCollider::RectCollider(EData* _data)  : Collider(_data, COLLISION_RECT) {}

vec2 RectCollider::GetCenteredLocation() const
{
    vec2 const DistanceToPivot = (vec2(0.5f, 0.5f) - m_Data->Pivot) * m_Data->Size; 
    vec2 CenteredLocation = m_Data->Location + DistanceToPivot;
    
    return CenteredLocation;
}

bool RectCollider::collides(Collider* other)
{
    m_CenteredLocation = GetCenteredLocation();
    
    bool const HasCollided = other->collides(m_CenteredLocation, m_Data->Size);

    if(HasCollided)
    {
        this->SetHasCollided(HasCollided);
        other->SetHasCollided(HasCollided);
    }
    
    return HasCollided;
}

bool RectCollider::collides(vec2& circlePos, float circleRadius)
{
    m_CenteredLocation = GetCenteredLocation();
    return checkCircleRect(circlePos, circleRadius, m_CenteredLocation, m_Data->Size);
}

bool RectCollider::collides(vec2& rectPos, vec2& rectSize)
{
    m_CenteredLocation = GetCenteredLocation();
    return checkRectRect(rectPos, rectSize, m_CenteredLocation, m_Data->Size);
}

bool RectCollider::collides(vec2& pixelsPos, vec2& pixelsSize, uint8_t* pixels)
{
    m_CenteredLocation = GetCenteredLocation();
    return checkPixelsRect(pixelsPos, pixelsSize, pixels, m_CenteredLocation, m_Data->Size);
}

#pragma endregion


#pragma region PixelsCollider

PixelsCollider::PixelsCollider(EData* _data, ltex_t* _tex) : Collider(_data, COLLISION_PIXELS), m_Tex(_tex) {}

bool PixelsCollider::collides(vec2& circlePos, float circleRadius)
{
    return false; //checkCirclePixels();
}

bool PixelsCollider::collides(vec2& rectPos, vec2& rectSize)
{
    return false; //checkPixelsRect();
}

bool PixelsCollider::collides(vec2& pixelsPos, vec2& pixelsSize, uint8_t* pixels)
{
    return false; //checkPixelsPixels();
}

bool PixelsCollider::collides(Collider* other)
{
    return false;
}

#pragma endregion