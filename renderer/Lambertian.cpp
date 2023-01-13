#include "Lambertian.h"



Vec3D Lambertian::apply(HitStruct &h) 
{
    Vec3D intersection = h.m_R.origin + (h.m_T*h.m_R.direction);
    Vec3D retColor;
    //intersection.print();
for (int i = 0; i < Lights.size(); i++){
Vec3D lcolor;
Light *light = Lights[i];

Vec3D lightpos = light->m_pos;
Vec3D intensity = light->m_intensity;

Vec3D L = lightpos - intersection;
L = L.normalize();
//L.print();

//CALCULATE R G AND B
Vec3D normal = h.normal;


double ndotl = normal.dot(L);
double max = std::max(0.0,ndotl);


lcolor[0] = intensity[0] * m_diffuse[0];
lcolor[1] = intensity[1] * m_diffuse[1];
lcolor[2] = intensity[2] * m_diffuse[2];


//SHADOWS

Ray sRay = ShadowRay(light,intersection);

bool sHit = anyHit(sRay,.00001,1.0,Shapes);

if (sHit == false){
    retColor = retColor + (max * lcolor); 
}

}

    
return retColor;
}




