#pragma once
#include <vector>
#include <queue>
#include <glfw3.h>

#include "litegfx.h"
#include "Vec2.h"


class Camera;
class Entity;

# pragma region DataManagement

struct EData {
    EData(vec2 _loc, vec2 _size, vec2 _scale = vec2(1,1), vec2 _pivot = vec2(0.5, 0.5), float angle = 0.f) :
    Location(_loc),
    NewLocation(_loc),
    Scale(_scale),
    Pivot(_pivot),
    Size(_size),
    Angle(angle){}

    ~EData() = default;

    vec2 TempLocation = vec2();
    vec2 Location;
    vec2 NewLocation;
    vec2 Scale;
    vec2 Pivot;
    vec2 Size;
    float Angle;
    
};

#pragma endregion


class World {
    
private:
    static World* instance;
    
    std::vector<Entity*> m_Entities;

    const float m_Red = 0.f;
    const float m_Green = 0.f;
    const float m_Blue = 0.f;


public:
    GLFWwindow* m_Window;
    float const Height = 800.f;
    float const Width = 800.f;
    
public:
    static World* GetWorld();
    void Update(float DeltaTime);

    
#pragma region Setters / Getters
    
    std::vector<Entity*>& GetEntities() { return m_Entities; }
    
    void AddEntity(Entity* _entity);
    void RemoveEntity(Entity* _entity);
    
#pragma endregion
    
};
