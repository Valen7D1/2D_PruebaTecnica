#include "camera.h"

void Camera::SetCameraLocation(vec2 _newLocation)
{
    m_Location = _newLocation;
    // Clamp x-coordinate
    if (m_Location.x < m_BottomBoundaries.x)
    {
        m_Location.x = m_BottomBoundaries.x;
    }
    else if (m_Location.x > m_TopBoundaries.x)
    {
        m_Location.x = m_TopBoundaries.x;
    }

    // Clamp y-coordinate
    if (m_Location.y < m_BottomBoundaries.y)
    {
        m_Location.y = m_BottomBoundaries.y;
        
    }
    else if(m_Location.y > m_TopBoundaries.y)
    {
        m_Location.y = m_TopBoundaries.y;
    }
}
