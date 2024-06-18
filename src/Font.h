#pragma once

#include "stb_truetype.h"
#include <litegfx.h>

class vec2;

stbtt_bakedchar* SetFont(const char* Filename);

class Font
{
private:
    Font();

public:
    ~Font();
    
    static Font* load (const char* filename, float height);
    float getHeight () const { return m_height; }
    vec2 getTextSize (const char* text) const;
    void draw (const char* text, const vec2& pos) const;

public:
    ltex_t* tex;
    stbtt_bakedchar* fontdata;

private:
   float m_height = 0.f;
};
