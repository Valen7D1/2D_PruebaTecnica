#pragma once


#include "Vec2.h"

class Utils
{
public:
    static float Dot(vec2 a, vec2 b);
    static vec2 Lerp(vec2 CurrentLocation, vec2 TargetLocation, vec2 Speed);
    static float Lerp(float CurrentRotation, float TargetRotation, float Speed);
    
};