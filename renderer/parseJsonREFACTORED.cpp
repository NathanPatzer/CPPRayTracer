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
#include "BVHNode.h"
#include <thread>

Framebuffer f;

void renderSegment(int width, int height,int rpp, Camera *cam, int depth, SceneContainer s,int wstart,int hstart,int thread)
{
int pixel = 0;
int threadw = 0;
int threadh = 0;
threadw = width - wstart;
threadh = height - hstart;
float percent = 0.0f;
int oldPercent = 0;
for (int j = hstart; j < height; j++)
{
    for (int i = wstart; i < width; i++)
    {
        Vec3D pixelColor(0,0,0);
        
        for (int p = 0; p < rpp; p++)
        {
            for (int q = 0; q < rpp; q++)
            {
                double offseti;
                double offsetj;
                offseti = (p + drand48())/rpp;
                offsetj = (q + drand48())/rpp;
                Ray ray;
                ray = cam->genRay(i,j,offseti,offsetj);
                pixelColor += s.rayColor(ray,1.0,1000000000.0,depth);
            }
        }
        pixel += 1;
        percent = (float)pixel /(float)(threadw * threadh);
        int realpercent = percent * 100;

        if (thread == 5 && realpercent % 5 == 0 && realpercent != oldPercent){
        oldPercent = realpercent;
        std::cout << realpercent << "%\n";
        }

        pixelColor = pixelColor / (rpp * rpp);
        f.setPixelColor(i,j,pixelColor);
    }
}
}





int main(int argc, char *argv[])
{


    sivelab::GraphicsArgs args;
    args.process(argc,argv);
    SceneContainer scenes;
    scenes.width = args.width;
    scenes.height = args.height;
    scenes.parseJSONData(args.inputFileName);
    int rpp = args.rpp;
    int depth = args.recursionDepth;
    
    Framebuffer fb(args.width,args.height);
    f = fb;
    
    Camera *cam = scenes.m_allCameras[0];
    
    
    scenes.root = new BVHNode(scenes.m_allShapes,0);
    scenes.m_background = Vec3D(.2,.2,.2);
    
    int num_threads = 10;
    int offy = fb.m_height / num_threads;
    
    
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; i++)
    {
        threads.push_back(std::thread (renderSegment,fb.m_width,(i + 1) * offy,rpp,cam,depth,scenes,0,offy * i,i+1));
    }

    for (int j = 0; j < num_threads; j++)
    {
        threads[j].join();
    }
    /*
    std::thread t1(renderSegment,fb.m_width,offy,rpp,cam,depth,scenes,0,0,1);
    std::thread t2(renderSegment,fb.m_width,2 * offy,rpp,cam,depth,scenes,0,offy,2);
    std::thread t3(renderSegment,fb.m_width,3 * offy,rpp,cam,depth,scenes,0,2*offy,3);
    std::thread t4(renderSegment,fb.m_width,4 * offy,rpp,cam,depth,scenes,0,3 * offy,4);
    std::thread t5(renderSegment,fb.m_width,5 * offy,rpp,cam,depth,scenes,0,4 * offy,5);
    std::thread t6(renderSegment,fb.m_width,6 * offy,rpp,cam,depth,scenes,0,5 * offy,6);
    std::thread t7(renderSegment,fb.m_width,7 * offy,rpp,cam,depth,scenes,0,6 * offy,7);
    std::thread t8(renderSegment,fb.m_width,8 * offy,rpp,cam,depth,scenes,0,7 * offy,8);
        
    //make main thread wait for these segments
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    */
f.exportAsPNG("render.png");




    return 0;
}


