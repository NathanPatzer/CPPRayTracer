#include "MirrorShader.h"



MirrorShader::MirrorShader()
{




}



Vec3D MirrorShader::apply(HitStruct &h){
    
    Vec3D intersection = h.m_R.origin + (h.m_T*h.m_R.direction);
    Vec3D v = -1.0 * h.m_R.direction;
    v = v.normalize();

    Vec3D n = h.normal.normalize();

    Vec3D r = (-1.0 * v) + (2.0 * v.dot(n) * n);
    Ray mirrorRay;
    mirrorRay.origin = intersection;
    mirrorRay.direction = r;
    

return scenePtr->rayColor(mirrorRay,1.0e-6,std::numeric_limits<double>::max(),depth-1);
}



