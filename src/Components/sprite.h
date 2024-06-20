#pragma once

#include "litegfx.h"

struct EData;

class Color
{
public:
    Color(float _r, float _g, float _b, float _a = 1.f) :
    r(_r), g(_g), b(_b), a(_a) {}
    
public:
    float getRed() const { return r; }
    float getGreen() const { return g; }
    float getBlue() const { return b; }
    float getAlpha() const { return a; }

    static Color White() { return Color(1.0f, 1.0f, 1.0f); }
    static Color Black() { return Color(0.0f, 0.0f, 0.0f); }
    static Color Gray() { return Color(0.5f, 0.5f, 0.5f); }
    static Color Red() { return Color(1.f, 0.f, 0.f); }
    static Color Yellow()   { return Color(1.0f, 1.0f, 0.0f); }
    static Color Orange()   { return Color(1.0f, 0.5f, 0.0f); }
    static Color Green()    { return Color(0.0f, 1.0f, 0.0f); }

    
    void SetColor();
    
private:
    float r, g, b, a; 
};


class Sprite
{
public:
    Sprite(ltex_t* tex, EData* _data,int hframes, int vframes, int fps, Color _color):
        m_Texture(tex),
        m_Data(_data),
        m_HFrames(hframes),
        m_VFrames(vframes),
        m_FPS(fps),
        m_FrameVSize(static_cast<float>(m_Texture->height/m_VFrames)),
        m_FrameHSize(static_cast<float>(m_Texture->width/m_HFrames)),
        m_TimeForFrame(1.f/m_FPS),
        m_color(_color) {}
    
    ~Sprite();

private:
    ltex_t* m_Texture = nullptr;
    EData* m_Data = nullptr;
    
    lblend_t m_Blend = BLEND_ALPHA;
    

    int m_HFrames = 0;
    int m_VFrames = 0;
    int m_FPS = 1;
    int m_CurrentHFrame = 0;
    int m_CurrentVFrame = 0;


    float m_FrameVSize;
    float m_FrameHSize;
    float m_TimeForFrame;
    
    float m_AcumulatedTime = 0.f;
    
    Color m_color = Color::White();
    
public:
    void SetLgfxColor () { m_color.SetColor(); }

    static ltex_t* loadImage(const char* filename);
    void update(float deltaTime);
    void draw() const;

#pragma region Setters/Getters
    // getters
    ltex_t* getTexture() const { return m_Texture; }
    EData* GetData() const { return m_Data; }
    lblend_t getBlend() const { return m_Blend; }
    int getHframes() const { return m_HFrames; }
    int getVframes() const { return m_VFrames; }
    int getFps() const { return m_FPS; }
    //int getCurrentFrame() const { return (m_CurrentHFrame + 1) * (m_CurrentVFrame + 1); }
    Color getColor() const { return m_color; }

    // setters
    void setTexture(ltex_t* tex, int hframes = 1, int vframes = 1);
    void SetData(EData* _data) { m_Data = _data; }
    void setBlend(lblend_t mode) { m_Blend = mode;}
    void setFps(int fps) { m_FPS = fps; }
    //void setCurrentFrame(int frame) { m_CurrentFrame = frame; }
    void setColor(Color _color) { m_color = _color; }

#pragma endregion
    
};