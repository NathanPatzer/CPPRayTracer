#pragma once
#include "Shader.h"
#include "HitStruct.h"
#include <algorithm>

class BlinnPhong : public Shader
{


public:
    BlinnPhong(const Vec3D &diffuse,const Vec3D &spec,const double &exp)
    {
    m_diffuse = diffuse;
    m_Spec = spec;
    m_Phong = exp;
    }

    ~BlinnPhong() {}

    Vec3D apply(HitStruct &h);


        Vec3D m_diffuse;
        Vec3D m_Spec;
        double m_Phong;




    
};