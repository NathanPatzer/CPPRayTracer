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
/*
//finds index of object in m_AllShapes
int findIndex(const Ray r, const SceneContainer sc)
{
    
    int index = -1; //default return, otherwise 0 or 1 for two shapes on the scene
    Ray tempRay = r;
    double t = 100000;
    for (int i = 0; i < sc.m_allShapes.size(); i++){
        if (sc.m_allShapes[i]->closestHit(tempRay)){
            //std::cout << "first";
            if (sc.m_allShapes[i]->m_T > 1){
                    if (sc.m_allShapes[i]->m_T < t){
                        index = i;
                        t = sc.m_allShapes[i]->m_T;
                    }
                }

        }

    }
    return index;
}
*/
int main(int argc, char *argv[])
{

    Vec3D black;
    Vec3D red(1.0,0,0);
    Vec3D green(0,1.0,0);

    Framebuffer fb(400,400);
    CoordSys crd(Vec3D(0,0,-1), Vec3D(0,1,0));
    int nx = fb.m_width;
    int ny = fb.m_height;
    Vec3D pos(0,0,0);
    //double Vec3D pos, double planeW, double focalLength, int dimx, int dimy, CoordSys crd
    Camera *per = new PerspectiveCamera(pos,0.5,.5,nx,ny,crd);
    
    //Sphere *sphere1 = new Sphere(Vec3D(0, 0, -5.0 ),1.2);
    Triangle *sphere1 = new Triangle(Vec3D(1, -1, -3 ),Vec3D(0,3,-5),Vec3D(-1,-1,-6));
    //Sphere *sphere1 = new Sphere(Vec3D(0, 0, -5.0 ),1.2);
    //Triangle *sphere2 = new Triangle(Vec3D(2, -1, -3 ),Vec3D(0,3,-6),Vec3D(-1,-1,-5));
    //Box *box = new Box(Vec3D(0,0,-3.0),Vec3D(1,1,-5.0));
    SceneContainer scene;

    //scene.addShape(tri);
    //scene.addShape(sphere);
   
    //scene.addShape(&Triangle( Vec3D(-1.0, -1.0, -5.0 ),  Vec3D( 1.0, -1.0, -5.0), Vec3D( 0.0, 1.0, -5.0)));  
    //scene.addShape(&Sphere(Vec3D(-1.0, -1.0, -5.0 ),.5));  
    //scene.addShape(box);
    scene.addShape(sphere1);
 /**
    hit = false
    for each object o in the group do
        if (o is hit at ray parameter t and t ∈ [t0, t1]) then
        hit = true
        hitobject = o
        t1 = t
        return hit
**/
    
    HitStruct h;
    //Shader *sPtr = new Lambertian(Vec3D(0,0,1));
    Shader *sPtr = new BlinnPhong(Vec3D(1,0,0),Vec3D(1,1,1),8.0);
    h.m_shadePtr = sPtr;
    Light *lPtr = new pointLight(Vec3D(0,0,2), Vec3D(1,1,1));
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
                        minT = h.m_T;
                        
                        //Ray shadowR = h.m_shadePtr->ShadowRay(lPtr,h.pointIntersect);
                
                        //crude shadow implemetnation
                        //if (scene.m_allShapes[k]->closestHit(shadowR,minT,maxT,h))
                        //{
                        //    fb.setPixelColor(i,j,Vec3D(.01,.01,.1));
                        //}
                        //else{
                              fb.setPixelColor(i,j,h.m_shadePtr->apply(h));
                            //fb.setPixelColor(i,j,Vec3D(0,1,0));
                        //}


                        
                    }
                    

                }   
                



            //int index = findIndex(r, scene);
            //std::cout << index << "\n";
            //Shape *o = scene.m_allShapes[k];
            //if (index == 0)
            //    fb.setPixelColor(i,j,red);
            //else if (index == 1)
            //    fb.setPixelColor(i,j,green);
            
            
               

            }
        }


    


 
    
fb.exportAsPNG("ball.png");




    return 0;
}