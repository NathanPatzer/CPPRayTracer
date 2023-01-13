#pragma once
#include "Vec3D.h"
#include "Ray.h"

class AABoundingBox
{
public:
    AABoundingBox(Vec3D min, Vec3D max) {
        minPt = min;
        maxPt = max;
    }

    AABoundingBox();

    bool intersect(const Ray r);
    AABoundingBox Union(const AABoundingBox rbox);
    void addPoint(const Vec3D point);
    
 

    //bounding box verticies
    Vec3D minPt;
    Vec3D maxPt;



};