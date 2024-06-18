#pragma once

#include "../Vec2.h"



class Camera
{
public:
    Camera(vec2 _startingLocation, vec2 _topBoundaries, vec2 _botBoundaries) :
    m_TopBoundaries(_topBoundaries),
    m_BottomBoundaries(_botBoundaries)
    {SetCameraLocation(_startingLocation);}

    ~Camera() = default;

    void SetCameraLocation(vec2 _newLocation);

    vec2 GetCameraLocation() { return m_Location; }
    
private:
    vec2 m_Location = vec2();
    vec2 m_TopBoundaries;
    vec2 m_BottomBoundaries;
};
