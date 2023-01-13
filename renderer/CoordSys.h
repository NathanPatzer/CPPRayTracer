#pragma once
#include "Vec3D.h"


class CoordSys
{
public: 
	CoordSys() : m_U(1,0,0), m_V(0,1,0), m_W(0,0,1)
	{}

    CoordSys(const Vec3D view, const Vec3D up);
	//W = -GAZE / length of gaze dir
	//U = (tempup X W) / length of tempup
	//V = W X U / length of W X U
	Vec3D m_U;
	Vec3D m_V;
	Vec3D m_W;


};
