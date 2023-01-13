#include "BVHNode.h"




BVHNode::BVHNode(std::vector<Shape*> shapes, int axis)
{

    if (shapes.size() == 0)
    {   
        
    }
    else if (shapes.size() == 1)
    {
        
        leftChild = shapes[0];
        rightChild = nullptr;
        boundingBox = shapes[0]->boundingBox;
    }
    else if (shapes.size() == 2)
    {
       
        leftChild = shapes[0];
        rightChild = shapes[1];
        boundingBox = shapes[0]->boundingBox.Union(shapes[1]->boundingBox);
    }
    else
    {
         
        AABoundingBox tempBox = shapes[0]->boundingBox;
        //build aabbox with all shapes
        
        for (int i = 1; i < shapes.size(); i++)
        {
            tempBox = tempBox.Union(shapes[i]->boundingBox);
        }
        boundingBox = tempBox;
        

        //split based on axis
        Vec3D split = (boundingBox.minPt + boundingBox.maxPt) / 2.0;
        std::vector<Shape*> leftShapes;
        std::vector<Shape*> rightShapes;
        
        //dump shapes into left or right vectors;
        for (int i = 0; i < shapes.size(); i++)
        {
            
            if (shapes[i]->centroid[axis] > split[axis])
            {
                
                rightShapes.push_back(shapes[i]);
            }
            else{
                leftShapes.push_back(shapes[i]);
            }
        }

        if (leftShapes.size() == 0)
        {
            
        }
        //create new BVHNodes
        leftChild = new BVHNode(leftShapes,(axis + 1) % 3);
        rightChild = new BVHNode(rightShapes,(axis + 1) % 3);
    }


}



bool BVHNode::closestHit( Ray r, double tMin, double tMax, HitStruct &hStruct)
{
bool leftHit = false;
bool rightHit = false;
HitStruct lH;
HitStruct rH;

if (boundingBox.intersect(r) == true)
{   
    if (leftChild != nullptr){
    leftHit = leftChild->closestHit(r,tMin,tMax,lH);
    }
    if (rightChild != nullptr){
    rightHit = rightChild->closestHit(r,tMin,tMax,rH);
    }
if (leftHit && rightHit)
{
    if (rH.m_T < lH.m_T)
    {
        hStruct = rH;
    }
    else
    {
        hStruct = lH;
    }
    return true;
}
else if (leftHit)
{
    hStruct = lH;
    return true;
}
else if (rightHit)
{
    hStruct = rH;
    return true;
}
else
{
    return false;
}


}

else{
    return false;
}



}