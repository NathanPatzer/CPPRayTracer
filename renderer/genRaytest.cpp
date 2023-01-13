#include "PerspectiveCamera.h"
#include "Framebuffer.h"
#include "Triangle.h"
#include "Sphere.h"

int main(int argc, char *argv[])
{

Vec3D b;
Framebuffer fb( 400,400 );
CoordSys crd;

Triangle triangle(Vec3D(-1.0,-1.0,-5.0),Vec3D(1.0,-1.0,-5.0),Vec3D(0.0,1.0,-5.0));

Camera *pCam = new PerspectiveCamera(.5,1.0,fb.m_width,fb.m_height,crd);
for (int j=0; j<fb.m_height; ++j) {
    for (int i=0; i<fb.m_width; ++i) {
        Ray r;
        r = pCam->genRay( i, j);
        Vec3D color = r.direction.normalize();
        color[0] = (color[0] + 1.0)/2.0;
        color[1] = (color[1] + 1.0)/2.0;
        color[2] = (color[2] + 1.0)/2.0;
        
         

        if (triangle.closestHit(r))
          fb.setPixelColor( i, j, color);
       else
          fb.setPixelColor( i, j, b);
    }
}
fb.exportAsPNG("ray.png");
return 0;
}
