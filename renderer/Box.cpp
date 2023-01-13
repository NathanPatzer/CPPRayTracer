#include "Box.h"



Box::Box(const Vec3D minPt, const Vec3D maxPt)
{
//DEFINE MAX (X,YZ) AND MIN (X,Y,Z)
double minx, miny, minz,maxx,maxy,maxz;
minx = minPt[0];
miny = minPt[1];
minz = minPt[2];
maxx = maxPt[0];
maxy = maxPt[1];
maxz = maxPt[2];
//DEFINE VERTICIES
    Vec3D p1(minx,maxy,minz);
    Vec3D p2(maxx,maxy,minz);
    Vec3D p3(maxx,miny,minz);
    Vec3D p4(maxx,miny,maxz);
    Vec3D p5(minx,maxy,maxz);
    Vec3D p6(minx,miny,maxz);

//DEFINE TRIANGLES

    
    Shape *tri1 = new Triangle(minPt,p3,p2);
    Shape *tri2 = new Triangle(minPt,p2,p1);
    Shape *tri3 = new Triangle(p3,maxPt,p4);
    Shape *tri4 = new Triangle(p3,p2,maxPt);
    Shape *tri5 = new Triangle(p4,p5,p6);
    Shape *tri6 = new Triangle(p4,maxPt,p5);
    Shape *tri7 = new Triangle(p6,minPt,p1);
    Shape *tri8 = new Triangle(p1,p5,p6);
    Shape *tri9 = new Triangle(p1,maxPt,p2);
    Shape *tri10 = new Triangle(p1,p5,maxPt);
    Shape *tri11 = new Triangle(minPt,p3,p4);
    Shape *tri12 = new Triangle(minPt,p4,p6);
    


    triArray.push_back(tri1); // DRAWN 
    triArray.push_back(tri2);   // DRAWN 
    triArray.push_back(tri3); // DRAWN 
    triArray.push_back(tri4); // DRAWN 
    triArray.push_back(tri5); // DRAWN 
    triArray.push_back(tri6); // DRAWN 
    triArray.push_back(tri7);   // DRAWN 
    triArray.push_back(tri8);   // DRAWN 
    triArray.push_back(tri9); // DRAWN 
    triArray.push_back(tri10); // DRAWN 
    triArray.push_back(tri11); // DRAWN 
    triArray.push_back(tri12); // DRAWN 

    

}




bool Box::closestHit(Ray r, double tMin, double tMax, HitStruct &h)
{

  
    return true;
}