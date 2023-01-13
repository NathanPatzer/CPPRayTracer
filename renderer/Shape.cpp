#include "Shape.h"


Shape::Shape()
{



}


void Shape::setName(const std::string name)
{
m_Name = name;
}

std::string Shape::getName()
{
return m_Name;
}


