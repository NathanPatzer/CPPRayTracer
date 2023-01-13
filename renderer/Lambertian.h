#pragma once
#include "Shader.h"
#include "HitStruct.h"
#include <algorithm>

class Lambertian : public Shader 
{


    public:
    Lambertian(const Vec3D &diffuse)
    {
        m_diffuse = diffuse;
    }
    ~Lambertian() {}
    Vec3D apply(HitStruct &h);


    Vec3D m_diffuse;









};