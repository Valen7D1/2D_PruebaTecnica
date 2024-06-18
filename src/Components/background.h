#pragma once

#include "litegfx.h"
#include "../Vec2.h"

class ParalaxBackground
{
public:
    ParalaxBackground(const char* _fileName, vec2 _initialPosition, vec2 _size, vec2 _moveSpeed, float _moveRatio, int _repsX=1, int _repsY=1);
    virtual ~ParalaxBackground() = default;
    
    void Update(float DeltaTime);
    void Draw() const;

#pragma region Setters / Getters
    
    unsigned int GetLayer() const { return m_Layer; }
    const ltex_t* GetBackground(size_t layer) const { return m_Tex; }
    float GetScrollRatio(size_t layer) const { return m_ScrollRatio; }
    const vec2& GetScrollSpeed(size_t layer) const { return m_ScrollSpeed;}

    void SetLayer(unsigned int _layer) { m_Layer = _layer; }
    void SetScrollRatio(float ratio) { m_ScrollRatio = ratio; }
    void SetScrollSpeed(vec2 speed) { m_ScrollSpeed = speed; }

#pragma endregion
    
    
private:
    vec2 m_Size;
    vec2 m_ScrollSpeed;
    vec2 m_BaseLocation;
    
    int m_ReplicationsX;
    int m_ReplicationsY;
    
    float m_ScrollRatio;
    unsigned int m_Layer = 0;
    
    ltex_t* m_Tex;
    

};