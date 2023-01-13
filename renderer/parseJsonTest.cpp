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


int main(int argc, char *argv[])
{


    sivelab::GraphicsArgs args;
    args.process(argc,argv);
    SceneContainer scenes;
    scenes.width = args.width;
    scenes.height = args.height;
    scenes.parseJSONData(args.inputFileName);


    
    Framebuffer fb(args.width,args.height);
    
    Light *light = scenes.m_allLights[0];
    Camera *cam = scenes.m_allCameras[0];
    
    fb.setBackground(Vec3D(.2,.2,.2));
    HitStruct h;

    h.scene = scenes;
        for (int j=0; j<fb.m_height; ++j) {
            for (int i=0; i<fb.m_width; ++i) {
            Ray r;
            r = cam->genRay(i,j);
            
                double maxT = 10000000000; 
                double minT = 1;
                for (int k = 0; k < scenes.m_allShapes.size(); k++){
                    h.m_shapePtr = scenes.m_allShapes[k];
                    
                    if (scenes.m_allShapes[k]->closestHit(r, minT,maxT, h)){
                            
                            h.m_shadePtr = scenes.m_Shaders[scenes.m_allShapes[k]->shaderName];
                            maxT = h.m_T;
                               fb.setPixelColor(i,j,h.m_shadePtr->apply(h));
                             
                    }
                }
           }

        }
       
fb.exportAsPNG("json2.png");




    return 0;
}