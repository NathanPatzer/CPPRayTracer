#pragma once

#include "Shape.h"


class Sphere : public Shape
{
public:

    Sphere(Vec3D center, double radius);

    bool closestHit( Ray r, double tMin, double tMax, HitStruct &h);
    

    double dot(const Vec3D& lhs, const Vec3D& rhs);
    Vec3D calculateNormal(const Ray r, const Vec3D center, const double T);
    void createBoundingBox();


    Vec3D m_Center;
    double m_radius;
    

};