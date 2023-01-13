#include "Shape.h"
#include "Triangle.h"

class Box : public Shape
{

public:
    Box(const Vec3D minPt,const Vec3D maxPt);
    bool closestHit (Ray r, double tMin, double tMax, HitStruct &h);

    

    






};