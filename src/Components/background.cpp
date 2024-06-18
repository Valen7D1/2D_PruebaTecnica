#include "background.h"

#include "Sprite.h"


ParalaxBackground::ParalaxBackground(const char* _fileName, vec2 _initialPosition, vec2 _size, vec2 _moveSpeed, float _moveRatio, int _repsX, int _repsY)
: m_Size(_size), m_ScrollSpeed(_moveSpeed), m_BaseLocation(_initialPosition), m_ReplicationsX(_repsX), m_ReplicationsY(_repsY), m_ScrollRatio(_moveRatio)
{
   m_Tex = Sprite::loadImage(_fileName);
}

void ParalaxBackground::Update(float DeltaTime)
{
    
}

void ParalaxBackground::Draw() const
{
    
}
