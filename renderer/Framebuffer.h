#pragma once
#include "Vec3D.h"
#include <vector>
#include <string>

//class Vec3
//{
//public:
 // float x, y, z;

//};


class Framebuffer
{

public:
  
  Framebuffer();
  Framebuffer(int w, int h);

  
  void setPixelColor(int locX, int locY, const Vec3D &rgb);
  Vec3D getPixelColor(int i, int j);
  void exportAsPNG(const std::string &filename);
  void setBackground(const Vec3D color);

	
  

  int m_width, m_height;
  std::vector<Vec3D> m_pixelArray;
};
