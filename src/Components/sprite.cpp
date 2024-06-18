#include "Sprite.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "../World.h"


void Color::SetColor()
{
    lgfx_setcolor(r, g, b, a);
}


Sprite::~Sprite()
{
    delete m_Texture;
}


void Sprite::setTexture(ltex_t* tex, int hframes, int vframes)
{
    m_Texture = tex;
    m_HFrames = hframes;
    m_VFrames = vframes;
}


void Sprite::update(float deltaTime)
{
    // first we need to get the current frame count
    m_AcumulatedTime += deltaTime;

    lgfx_setblend(m_Blend);
    SetLgfxColor();

    if (m_AcumulatedTime >= m_TimeForFrame)
    {
        m_AcumulatedTime -= m_TimeForFrame;

        // update Horizontal frames
        ++ m_CurrentHFrame;
        m_CurrentHFrame = m_CurrentHFrame % m_HFrames;

        // update Vertical frames only if Horizontal frames has been reset
        if (m_CurrentHFrame == 0)
        {
            ++m_CurrentVFrame;
            m_CurrentVFrame = m_CurrentVFrame % m_VFrames;
        }
    }
    // Draw using current values
    draw();
}


void Sprite::draw() const
{
    // top left and bottom right corners of texture
    vec2 m_TopLeft;
    vec2 m_BotRight;
        
    // get locations of texture using current frame values and sizes of texture
    m_TopLeft.x = (m_CurrentHFrame * m_FrameHSize) / m_Texture->width;
    m_TopLeft.y = (m_CurrentVFrame * m_FrameVSize) / m_Texture->height;
    m_BotRight.x = ((m_CurrentHFrame + 1) * m_FrameHSize) / m_Texture->width;
    m_BotRight.y = ((m_CurrentVFrame + 1) * m_FrameVSize) / m_Texture->height;
    
    ltex_drawrotsized(
    m_Texture, m_Data->Location.x,  m_Data->Location.y,  m_Data->Angle, m_Data->Pivot.x, m_Data->Pivot.y,
    m_Data->Size.x * m_Data->Scale.x, m_Data->Size.y * m_Data->Scale.y,
    m_TopLeft.x, m_TopLeft.y, m_BotRight.x, m_BotRight.y);
}


ltex_t* Sprite::loadImage(const char* filename)
{
    // carga de imagen
    int imgX;
    int imgY;
    unsigned char* pixels = stbi_load(filename, &imgX, &imgY, nullptr, 4);

    // seteo de tex
    ltex_t* tex = ltex_alloc(imgX, imgY, 1);

    // crea la representaciona  pixeles de tex
    ltex_setpixels(tex, pixels);

    return tex;
}
