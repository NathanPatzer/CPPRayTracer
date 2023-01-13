#pragma once
#include "Camera.h"
#include <vector>
#include "Light.h"
#include <map>
#include "../jsonnohlman/json/single_include/nlohmann/json.hpp"
#include <stack>
#include <glm/gtx/string_cast.hpp>
#include <map>
#include <utility>
#include "HitStruct.h"
#include "Shape.h"
#include "BVHNode.h"
#include "Shader.h"
//class Shader;
//class Shape;
//class HitStruct;

class SceneContainer
{
public:
	SceneContainer() {}

	//Json parser functions
	glm::mat4 parseTransformData( nlohmann::json &transformData );
	Shape *extractAndCreateShapeFromJSONData( nlohmann::json &shapeData );
	void parseJSONData(const std::string &filename);

	void addShape(Shape *shape){
	m_allShapes.push_back(shape);
	}

	void addCamera(Camera *camera){
	m_allCameras.push_back(camera);
	}

	void addLight(Light *light){
	m_allLights.push_back(light);
	}	
	
	Vec3D rayColor(const Ray r,double minT, double maxT, int depth);
	
	

	std::vector<Camera*> m_allCameras;
	std::vector<Light*> m_allLights;
	std::vector<Shape*> m_allShapes;
	std::map<std::string, Shader*> m_Shaders;
	Vec3D bg;
	
	double height,width;


	Shape *root;

	Vec3D m_background;

	

};
