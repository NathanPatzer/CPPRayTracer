#include "PerspectiveCamera.h"
#include "Framebuffer.h"
#include "Shape.h"
#include "Triangle.h"
#include "Sphere.h"
#include "SceneContainer.h"
#include "HitStruct.h"
#include "Shader.h"
#include "Lambertian.h"
#include "Light.h"
#include "pointLight.h"
#include "BlinnPhong.h"
#include "Box.h"
#include <fstream>
#include "handleGraphicsArgs.h"
#include "Camera.h"
#include "MirrorShader.h"
#include <stdlib.h>
#include "AABoundingBox.h"
#include "Vec3D.h"

int main(int argc, char *argv[])
{


Framebuffer fb(500,250);

Triangle tri( Vec3D(200, 40, 0 ),  Vec3D( 250, 80, 0 ), Vec3D( 225, 200, 0 ) );
fb.setBackground(Vec3D(1.0, 0.25, 1.0));

Vec3D triColor = Vec3D(0.2, 1.0, 0.25);
Vec3D minPt = tri.boundingBox.minPt;
Vec3D maxPt = tri.boundingBox.maxPt;

/*
[xmin, ymin, xmax, ymax] = findBoundingBoxOfTriangle
for y in [ymin, ymax]
   for x in [xmin, xmax]
      [alpha, beta, gamma] = computeBarycentricCoordOfTriangle
      if (alpha > 0 & beta > 0 & gamma > 0)
          setPixelColor(x,y, triangleColor)
*/

for (int y = minPt[1]; y < maxPt[1]; y++)
{
    for (int x = minPt[0]; x < maxPt[0]; x++)
    {
        tri.calculateBarycentric(x,y);

        if (tri.m_Alpha > 0 && tri.m_Beta > 0 && tri.m_Gamma > 0)
        {
            fb.setPixelColor(x,y,triColor);
        }

    }
}

fb.exportAsPNG("raster.png");

return 0;
}