#pragma once

#include "Shape.h"
#include "HitStruct.h"

class Triangle : public Shape
{
public:
	
	Triangle(Vec3D a, Vec3D b, Vec3D c);

	bool closestHit( Ray r, double tMin, double tMax, HitStruct &h);
    Vec3D calculateNormal(Vec3D A, Vec3D B, Vec3D C);   
	void createBoundingBox();
	void calculateBarycentric(double x, double y);
	double implicitLine(Vec3D A, Vec3D B, double x, double y);
//member variables for the verticies
	Vec3D m_a, m_b, m_c;
	
	double m_Alpha,m_Beta,m_Gamma;

};

