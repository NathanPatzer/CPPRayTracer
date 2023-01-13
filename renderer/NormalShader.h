#pragma once
#include "Shader.h"


class NormalShader : public Shader
{

public:


    NormalShader() {}
    Vec3D apply(const HitStruct &h) const
    {
     Vec3D norm = h.normal;

     return norm;
    }


    

    };