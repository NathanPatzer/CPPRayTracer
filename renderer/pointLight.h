#pragma once
#include "Vec3D.h"

class pointLight : public Light 
{

public:
    pointLight(Vec3D Position, Vec3D intensity)
    {
        m_intensity = intensity;
        m_pos = Position;
    }

    
    



};