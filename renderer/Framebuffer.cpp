#include "Framebuffer.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "png++/png.hpp"
#include "handleGraphicsArgs.h"
#include "Random.h"


using namespace sivelab;

Framebuffer::Framebuffer()
  : m_width(100), m_height(100),
                    m_pixelArray(m_width * m_height)
{
    //set all pixels to 0.0
  for (int i = 0; i < m_pixelArray.size(); i++) {
    m_pixelArray[i][0] = 0.0;
    m_pixelArray[i][1] = 0.0;
    m_pixelArray[i][2] = 0.0;
  }
}

Framebuffer::Framebuffer(int w, int h)
  : m_width(w), m_height(h),
                  m_pixelArray(m_width * m_height * 3)

{
//set all to 0.0

    for (int i = 0; i < m_pixelArray.size(); i++) {
         m_pixelArray[i][0] = 0.0;
         m_pixelArray[i][1] = 0.0;
         m_pixelArray[i][2] = 0.0;
    }
}

//set the (i,j) pixel a certain color defined by the rgb argument
//
void Framebuffer::setPixelColor(int locX, int locY, const Vec3D &rgb)
{
  //math to find pixel location on a 2d grid
  int index = locY * m_width + locX;

  //set pixel to rgb color
  m_pixelArray[index] = rgb;
}

//get pixel color on the 2d grid
Vec3D Framebuffer::getPixelColor(int locX, int locY)
{
  int index = locY * m_width + locX;
    
  

  return m_pixelArray[index];
}

void Framebuffer::exportAsPNG(const std::string& filename) 
{
  
  int w = m_width, h = m_height;
  png::image<png::rgb_pixel> imData(w, h);

    int index = 0;


  for (unsigned int idx = 0; idx < m_height * m_width; ++idx) {
      size_t x = idx % w;
      auto y = static_cast<size_t>(floor(idx / static_cast<float>(imData.get_width())));
      if (m_pixelArray[idx][0] > 1.0){
          m_pixelArray[idx][0] = 1.0;
      }
      if (m_pixelArray[idx][1] > 1.0){
          m_pixelArray[idx][1] = 1.0;
      }
      if (m_pixelArray[idx][2] > 1.0){
          m_pixelArray[idx][2] = 1.0;
      }
      // non-checking equivalent of image.set_pixel(x, y, ...);
      imData[m_height - 1 - y][x] = png::rgb_pixel((int)(255 * m_pixelArray[idx][0]), (int)(255 * m_pixelArray[idx][1]), (int)(255 * m_pixelArray[idx][2]));
    }
    imData.write(filename);
  
  
}

void Framebuffer::setBackground(const Vec3D color)
{

  for (int i = 0; i < m_pixelArray.size(); i++){
      m_pixelArray[i] = color;
  }


}


