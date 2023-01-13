#include "PerspectiveCamera.h"
#include "Framebuffer.h"

int main(int argc, char *argv[])
{
    Framebuffer fb(350,250);
    CoordSys crd(Vec3D(0,-1,0), Vec3D(0,1,0));
    int nx = fb.m_width;
    int ny = fb.m_height;
    Vec3D pos(-19,12,3);
    //double Vec3D pos, double planeW, double focalLength, int dimx, int dimy, CoordSys crd
    Camera *per = new PerspectiveCamera(pos,0.5,.15,nx,ny,crd);

for (int j=0; j<fb.m_height; ++j) {
    for (int i=0; i<fb.m_width; ++i) {
         Ray r;
         r = per->genRay(i,j);

         Vec3D color = r.direction.normalize();

         //map direction [-1,1] to color [0,1] 
         color[0] = (color[0] + 1)/2;
         color[1] = (color[1] + 1)/2;
         color[2] = (color[2] + 1)/2;
         
         fb.setPixelColor(i,j,color);

    }
}
    
fb.exportAsPNG("per.png");

return 0;
}
