#include "BlinnPhong.h"





Vec3D BlinnPhong::apply(HitStruct &h)
{
Vec3D color;
Vec3D intersection = h.m_R.origin + (h.m_T*h.m_R.direction);

for (int i = 0; i < Lights.size(); i++){
Vec3D lcolor;
Light *light = Lights[i];

Vec3D lightpos = light->m_pos;
Vec3D intensity = light->m_intensity;
Vec3D L = lightpos - intersection;

L = L.normalize();
Vec3D V = -1.0 * h.m_R.direction; //Reverse rays direction to get V
V = V.normalize();                //normaluze V
Vec3D H = V + L;                  //Calculate H
H = H.normalize();                //normalize H
Vec3D normal = h.normal;          


//CALCULATE SPECULAR COMPONENET
double phongMax;
phongMax = std::max(0.0,normal.dot(H)); 
phongMax = pow(phongMax,m_Phong);        //raise phongmax to the phong exponent
Vec3D Specular;
Specular[0] = m_Spec[0] * intensity[0];  //multiply the specular vector by the intensity vector
Specular[1] = m_Spec[1] * intensity[1];  
Specular[2] = m_Spec[2] * intensity[2];
Specular = phongMax * Specular;         //multiply the phongmax by that product



//CALCULATE DIFFUSE COMPONENET
double ndotl = normal.dot(L);
double max = std::max(0.0,ndotl);


lcolor[0] = intensity[0] * m_diffuse[0];
lcolor[1] = intensity[1] * m_diffuse[1];
lcolor[2] = intensity[2] * m_diffuse[2];
lcolor = max * lcolor; 

//ADD DIFFUSE TO THE SPECULAR COMPONENET

//color.print();

//SHADOWS

Ray sRay = ShadowRay(light,intersection);

bool sHit = anyHit(sRay,.00001,1.0,Shapes);

if (sHit == false){
    color = color + (lcolor + Specular);
}

}


return color;
}