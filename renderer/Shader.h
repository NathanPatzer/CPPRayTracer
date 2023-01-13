#pragma once
#include "Vec3D.h"
//#include "HitStruct.h"
#include "Ray.h"
#include "Light.h"
#include "Shape.h"
#include "BVHNode.h"
class HitStruct;
class SceneContainer;

class Shader
{
public:
	Shader();

	~Shader() {}
	Shader(const Vec3D &ambient);
	
	virtual Vec3D apply(HitStruct &h) 
	{
		return m_ambient;
	}

	void setName(std::string name){
		m_name = name;
	}

	Ray ShadowRay(Light *l, Vec3D intersect) const;
	bool anyHit(Ray shadowRay, double tMin,double tMax, std::vector<Shape*> shapes);
	
	std::vector<Light*> Lights;
	std::vector<Shape*> Shapes;
	std::string type;
	SceneContainer *scenePtr;
	Shape* bvh;
    int depth;
protected:
	Vec3D m_ambient;
	std::string m_name;
	






};
