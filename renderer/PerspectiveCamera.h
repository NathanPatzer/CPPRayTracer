#pragma once
#include "Ray.h"
#include "Camera.h"
#include "Vec3D.h"


class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(Vec3D pos, double planeW, double focalLength, int dimx, int dimy, CoordSys crd);



	Ray genRay(int i, int j,double offI,double offJ);

	float left;
	float right;
	float bottom;
	float top;
	

};

