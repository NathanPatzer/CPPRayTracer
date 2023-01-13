#include "SceneContainer.h"





Vec3D SceneContainer::rayColor(const Ray r,double minT, double maxT,int depth)
{

if (depth == 0){
    return m_background;
}
else{
HitStruct h;


Vec3D color;
bool isBG = true;



if (root->closestHit(r,minT,maxT,h))
{
        h.m_shadePtr = m_Shaders[h.m_shapePtr->shaderName];
                
        h.m_shadePtr->Lights = m_allLights;
        h.m_shadePtr->Shapes = m_allShapes;
        h.m_shadePtr->scenePtr = this;
        h.m_shadePtr->depth = depth;
        h.m_shadePtr->bvh = root;
        color = h.m_shadePtr->apply(h);
        isBG = false;
}

if (isBG == false)
    return color;
else   
    return m_background;
}
}




