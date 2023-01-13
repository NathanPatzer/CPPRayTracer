#include "Sphere.h"



Sphere::Sphere(Vec3D center, double radius)
{
m_Center = center;
m_radius = radius;

centroid = m_Center;
createBoundingBox();
}



bool Sphere::closestHit(Ray r, double tMin, double tMax, HitStruct &h)
{
    
    Vec3D oc = r.origin - m_Center;
    double a = dot(r.direction,r.direction);
    double b = 2.0 * dot(oc, r.direction);
    double c = dot(oc,oc) - (m_radius * m_radius);
    double disc = (b * b) - (4 * a * c);

    
    if (disc < 0) {
        return false;
    }
    else {
        
        m_T = (-b - sqrt(disc) ) / (2.0*a);
        /*
        //NEW CALCULATION FOR T
    
        double Tmiddle = dot(m_Center - r.origin,r.direction);
        Vec3D intersection = r.origin + (Tmiddle * r.direction);
        Vec3D yvec = m_Center - intersection;
        double Y = yvec.length();

        double X = sqrt(m_radius * m_radius - Y * Y);

        m_T = Tmiddle - X;

        
        //END NEW T CALCULATION
        */

        if (m_T < tMin || m_T > tMax ){
            return false;
        }
        else{
        //normal calculation
        Vec3D N = calculateNormal(r,m_Center,m_T);
        h.normal = N;
        h.m_T = m_T;
        h.m_R = r;
        
        h.m_shapePtr = this;
        return true;
        }
    }

}

double Sphere::dot(const Vec3D& lhs, const Vec3D& rhs)
{
    double product = 0.0;

    product = (lhs[0] * rhs[0]) + (lhs[1] * rhs[1]) + (lhs[2] * rhs[2]);


    return product;
}

Vec3D Sphere::calculateNormal(const Ray r, const Vec3D center, const double T)
{

    Vec3D intersection;
    intersection = r.origin + (T * r.direction);
    Vec3D norm = intersection - center;
    norm = norm.normalize();
    return norm;

}

void Sphere::createBoundingBox()
{
Vec3D center = m_Center;
double radius = m_radius;

//calculate min point
Vec3D min;

min[0] = center[0] - radius;
min[1] = center[1] - radius;
min[2] = center[2] - radius;

//calculate max point
Vec3D max;

max[0] = center[0] + radius;
max[1] = center[1] + radius;
max[2] = center[2] + radius;

boundingBox = AABoundingBox(min,max);
}