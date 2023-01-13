#pragma once
#include "Vec3D.h"
#include "CoordSys.h"
#include "Ray.h"



class Camera
{
public:
	Camera() : m_CoordSys(), m_pos(0,0,0) {}

	Camera(CoordSys crd) : m_pos(0,0,0) { m_CoordSys = crd;}

	

	virtual Ray genRay(int i, int j, double offI, double offJ) = 0; //return ray


//protected:
	CoordSys m_CoordSys;
	Vec3D m_pos;
	double imgW;
	double imgH;
	double focal;
	int nx;
	int ny;
	float left;
	float right;
	float bottom;
	float top;



};





