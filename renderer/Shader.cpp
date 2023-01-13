#include "Shader.h"



Shader::Shader()
{
        int rr = rand() % 10;
		int rb = rand() % 10;
		int rg = rand() % 10;

		double red = (double) rr / 10.0;
		double green = (double) rg / 10.0;
		double blue = (double) rb / 10.0;
		m_ambient = Vec3D(red,green,blue);



}

Shader::Shader(const Vec3D &ambient)
	{
		m_ambient = ambient;
	}

Ray Shader::ShadowRay(Light *l,Vec3D intersect) const
{
Ray Shadow;
Shadow.origin = intersect;
Shadow.direction = l->m_pos - intersect;

return Shadow;
}


bool Shader::anyHit(Ray shadowRay, double tMin,double tMax, std::vector<Shape*> shapes)
	{


		HitStruct hStruct;
		return bvh->closestHit( shadowRay, tMin, tMax, hStruct);
	}
