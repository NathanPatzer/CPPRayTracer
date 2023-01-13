#include "AABoundingBox.h"



AABoundingBox::AABoundingBox()
{

}


bool AABoundingBox::intersect(const Ray r)
{

//variables for checking overlaps
double txMin,txMax,tyMin,tyMax,tzMin,tzMax;

//X
double invX = 1.0/r.direction[0];
if (invX >= 0.0)
{
    txMin = invX * (minPt[0] - r.origin[0]);
    txMax = invX * (maxPt[0] - r.origin[0]);
}
else{
    txMin = invX * (maxPt[0] - r.origin[0]);
    txMax = invX * (minPt[0] - r.origin[0]);
}

//Y
double invY = 1.0/r.direction[1];
if (invY >= 0.0)
{
    tyMin = invY * (minPt[1] - r.origin[1]);
    tyMax = invY * (maxPt[1] - r.origin[1]);
}
else{
    tyMin = invY * (maxPt[1] - r.origin[1]);
    tyMax = invY * (minPt[1] - r.origin[1]);
}

//Z
double invZ = 1.0/r.direction[2];
if (invZ >= 0.0)
{
    tzMin = invZ * (minPt[2] - r.origin[2]);
    tzMax = invZ * (maxPt[2] - r.origin[2]);
}
else{
    tzMin = invZ * (maxPt[2] - r.origin[2]);
    tzMax = invZ * (minPt[2] - r.origin[2]);
}



if ( (txMin >  tyMax) || (tyMin > txMax) || (txMin > tzMax) || (tzMin > txMax) || (tyMin > tzMax) || (tzMin > tyMax) )
{
    return false;
}
else
{
    return true;
}

}

AABoundingBox AABoundingBox::Union(const AABoundingBox rbox)
{
Vec3D uMin;
Vec3D uMax;

//minimum
for (int i = 0; i < 3; i++){
    if (minPt[i] < rbox.minPt[i])
    {
        uMin[i] = minPt[i];
    }
    else{
        uMin[i] = rbox.minPt[i];
    }

}

//maximum
for (int i = 0; i < 3; i++){
    if (maxPt[i] > rbox.maxPt[i])
    {
        uMax[i] = maxPt[i];
    }
    else{
        uMax[i] = rbox.maxPt[i];
    }

}

double eps = 1e-6;
for (int i = 0; i < 3; i++)
{
    if (uMax[i] + eps > uMin[i] && uMax[i] - eps < uMin[i] )
    {
            uMax[i] += eps;
            uMin[i] -= eps;
    }
}


AABoundingBox uBox(uMin,uMax);

return uBox;
}

void AABoundingBox::addPoint(const Vec3D point)
{




}

