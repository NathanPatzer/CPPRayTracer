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
#include "NormalShader.h"
#include "MirrorShader.h"
int main(int argc, char *argv[])
{

    Framebuffer fb(400,400);
    
    CoordSys crd(Vec3D(0,0,-1), Vec3D(0,1,0));
    int nx = fb.m_width;
    int ny = fb.m_height;
    //Vec3D pos(-8,4,4);
     Vec3D pos(0,0,0);
    //double Vec3D pos, double planeW, double focalLength, int dimx, int dimy, CoordSys crd
    Camera *per = new PerspectiveCamera(pos,0.5,1.0,nx,ny,crd);
    
   
    


    Sphere *test1 = new Sphere(Vec3D(0, 0, -5.0 ),1.2);
    //Triangle *test2 = new Triangle(Vec3D(1, -1, -3 ),Vec3D(0,3,-5),Vec3D(-1,-1,-6));
    //Box *box = new Box(Vec3D(-.5,-.5,-.5),Vec3D(.5,.5,.5));
    SceneContainer scene;
    
    //scene.m_allShapes = box->triArray;
    /*
    scene.addShape(sphere1);
    scene.addShape(sphere2);
    scene.addShape(sphere3);
    scene.addShape(sphere4);

    scene.addShape(tri1);
    scene.addShape(tri2);
    scene.addShape(tri3);
    scene.addShape(tri4);
    */
    scene.addShape(test1);
    //scene.addShape(test2);
    HitStruct h;
    
    //Shader *sPtr = new Lambertian(Vec3D(0.957, 0.957, 0.941));
    Shader *sPtr = new MirrorShader();
    ///Shader *sPtr = new BlinnPhong(Vec3D(1,0,0),Vec3D(1,1,1),8.0);
    h.m_shadePtr = sPtr;
    Light *lPtr = new pointLight(Vec3D(0,4,4), Vec3D(1, 1, 1));
    scene.addLight(lPtr);
    h.scene = scene;

        for (int j=0; j<fb.m_height; ++j) {
            for (int i=0; i<fb.m_width; ++i) {
            Ray r;
            r = per->genRay(i,j);

                double maxT = 1000000; 
                double minT = 1;
                for (int k = 0; k < scene.m_allShapes.size(); k++){
                    h.m_shapePtr = scene.m_allShapes[k];
                    if (scene.m_allShapes[k]->closestHit(r, minT,maxT, h)){
                            maxT = h.m_T;
                

                             fb.setPixelColor(i,j,h.m_shadePtr->apply(h));
                             
                    }
            }
        }

        }
    


 
    
fb.exportAsPNG("box.png");




    return 0;
}