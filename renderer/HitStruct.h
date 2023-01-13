#pragma once

#include "Vec3D.h"
#include "Ray.h"
//#include "SceneContainer.h"

class Shape;
class Shader;


class HitStruct {

    
    public:
        HitStruct() {}

        Shader *m_shadePtr;
        Vec3D m_Color;
        Ray m_R;
        float m_T;
        Shape *m_shapePtr;
        Vec3D normal;
        
        //SceneContainer scene;
        Vec3D pointIntersect = m_R.origin + (m_T*m_R.direction);
    
};