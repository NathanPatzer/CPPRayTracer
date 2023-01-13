#pragma once
#include "Ray.h"
#include "Vec3D.h"
#include "HitStruct.h"
#include <limits>    
#include "AABoundingBox.h"
#include <vector>
//class HitStruct;

class Shape
{

public:
	Shape();
	
	
	virtual bool closestHit (Ray r, double tMin, double tMax, HitStruct &h) = 0;
	void setName(const std::string name);
	std::string getName();
	bool anyHit(Ray shadowRay, double tMin,double tMax, std::vector<Shape*> shapes);
	
	double m_T = 1000.0;
	std::string m_Name = "Not set";
	std::string shaderName;
	std::string type;
	std::vector<Shape*> triArray;

	//bounding box
	AABoundingBox boundingBox;
	Vec3D centroid;
};



