#include "Shader.h"
#include "SceneContainer.h"

class MirrorShader : public Shader
{

public:
    MirrorShader();
    Vec3D apply(HitStruct &h);

    Vec3D reflect(Vec3D v, Vec3D n);

    
    
    






};