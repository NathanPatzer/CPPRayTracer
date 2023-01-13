#include "PerspectiveCamera.h"


PerspectiveCamera::PerspectiveCamera(Vec3D pos, double planeW, double focalLength, int dimx, int dimy, CoordSys crd){
	imgW = planeW;
	focal = focalLength;
	nx = dimx;
	ny = dimy;
	m_CoordSys = crd;
	double temp = (double) ny / (double) nx;
	imgH = imgW * temp; 
	m_pos = pos;
	left = -imgW / 2.0;
	right = imgW / 2.0;
	bottom = -imgH / 2.0;
	top = imgH / 2.0;
}


Ray PerspectiveCamera::genRay(int i, int j,double offI,double offJ)
{
	Ray r;
	
	float u = left + (right - left) * ((i + offI) / nx);
	float v = bottom + (top - bottom) * ((j + offJ) / ny);

	r.origin = m_pos;
	r.direction = -1.0 * focal * m_CoordSys.m_W + u*m_CoordSys.m_U + v*m_CoordSys.m_V;

	return r;
}
