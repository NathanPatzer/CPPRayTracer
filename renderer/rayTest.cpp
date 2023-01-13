#include "Vec3D.h"
#include "Ray.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Shape.h"
#include "Triangle.h"
#include "Sphere.h"

int main(int argc, char *argv[])
{
Vec3D U(1,0,0), V(0,1,0), W(0, 0, 1);float focalLength = 1.0;float imagePlaneWidth = 0.5;float imagePlaneHeight = 0.5;float leftIP = -imagePlaneWidth / 2.0;float rightIP = imagePlaneWidth / 2.0;float bottomIP = -imagePlaneHeight / 2.0;
float topIP = imagePlaneHeight / 2.0;

Vec3D t;
Vec3D s;
Vec3D b;
bool f = false;
t[0] = 1.0;
s[1] = 1.0;
double u = 0.0;
double v = 0.0;
Framebuffer frameBuffer(400,400);

Triangle triangle(Vec3D(-1.0,-1.0,-5.0),Vec3D(1.0,-1.0,-5.0),Vec3D(0.0,1.0,-5.0));

Sphere sphere(Vec3D(0,0,-1), 0.05);

//triangle
for (int i=0; i<frameBuffer.m_width; i++)
    for (int j=0; j<frameBuffer.m_height; j++) {
       Ray r;
       r.origin = Vec3D(0.0, 0.0, 0.0);

       // this will only work for a square image... make sure to check types!
       u = leftIP + (rightIP - leftIP) * (i + 0.5)/frameBuffer.m_width;
       v = bottomIP + (topIP - bottomIP) * (j + 0.5)/frameBuffer.m_height;
       r.direction = -1.0 * focalLength * W + u * U + v * V;
       

       if (triangle.closestHit(r))
          frameBuffer.setPixelColor( i, j, t);
       else
          frameBuffer.setPixelColor( i, j, b);
    }

for (int i=0; i<frameBuffer.m_width; i++)
    for (int j=0; j<frameBuffer.m_height; j++) {
       Ray r2;
       r2.origin = Vec3D(0.0, 0.0, 0.0);

       // this will only work for a square image... make sure to check types!
       u = leftIP + (rightIP - leftIP) * (i + 0.5)/frameBuffer.m_width;
       v = bottomIP + (topIP - bottomIP) * (j + 0.5)/frameBuffer.m_height;
       r2.direction = -1.0 * focalLength * W + u * U + v * V;
       

       if (sphere.closestHit(r2))
          frameBuffer.setPixelColor( i, j, s);
       //else
         // frameBuffer.setPixelColor( i, j, b);
    }

frameBuffer.exportAsPNG("Tri.png");
}
//nx = width and height in pixels

