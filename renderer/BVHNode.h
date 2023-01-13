#pragma once
#include "Shape.h"
#include "Triangle.h"

class BVHNode : public Shape
{

public:
    BVHNode() {}
    BVHNode(std::vector<Shape*> Shapes, int axis);
    bool closestHit( Ray r, double tMin, double tMax, HitStruct &hStruct);


    Shape *leftChild;
    Shape *rightChild;

    
    
};