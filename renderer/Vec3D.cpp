#include "Vec3D.h"

Vec3D::Vec3D()
    : data(3)
{
    data[0] = data[1] = data[2] = 0.0;
}

Vec3D::Vec3D(const double x, const double y, const double z)
    : data(3)
{
    data[0] = x;
    data[1] = y;
    data[2] = z;
}

Vec3D::Vec3D(const Vec3D &v )
	: data(3)
{
    data[0] = v[0];
    data[1] = v[1];
    data[2] = v[2];
}

Vec3D &Vec3D::operator+=(const Vec3D &rhs)
{
    data[0] += rhs[0];
    data[1] += rhs[1];
    data[2] += rhs[2];
    return *this;
}

//print function for vectors
void Vec3D::print()
{
    std::cout << "(" << data[0] << "," << data[1] << "," << data[2] << ")\n";
}

Vec3D operator+(const Vec3D& lhs, const Vec3D& rhs)
    {
        //return Vec3D(1,1,1);
        return Vec3D( lhs[0]+rhs[0], 
                                lhs[1]+rhs[1],
                                lhs[2]+rhs[2] );
    }

Vec3D operator*(const double lhs, const Vec3D& rhs)
{
Vec3D mult;
	mult[0] = rhs[0] * lhs;
	mult[1] = rhs[1] * lhs;
	mult[2] = rhs[2] * lhs;

	return mult;
}

Vec3D operator/(const Vec3D& lhs, const double rhs)
{
    Vec3D div;
        div[0] = lhs[0] / rhs;
        div[1] = lhs[1] / rhs;
        div[2] = lhs[2] / rhs;


        return div;
}

Vec3D Vec3D::crossProduct(const Vec3D& rhs) 
{
Vec3D cross(0,0,0);
    cross[0] = (data[1] * rhs[2]) - (data[2] * rhs[1]);
    cross[1] = (data[2] * rhs[0]) - (data[0] * rhs[2]);
    cross[2] = (data[0] * rhs[1]) - (data[1] * rhs[0]);
return cross;
}



Vec3D Vec3D::normalize()
{
    Vec3D norm;
    Vec3D temp;
    temp[0] = data[0];
    temp[1] = data[1];
    temp[2] = data[2];

    norm[0] = temp[0]/temp.length();
    norm[1] = temp[1]/temp.length();
    norm[2] = temp[2]/temp.length();

    return norm;
}


Vec3D operator-(const Vec3D& lhs,const Vec3D& rhs)
{
    Vec3D min;
    min[0] = lhs[0] - rhs[0];
    min[1] = lhs[1] - rhs[1];
    min[2] = lhs[2] - rhs[2];
return min;
}

void Vec3D::operator=(const std::string string)
{

double p1,p2,p3;
std::stringstream s;

s << string;

s >> p1 >> p2 >> p3;


Vec3D stringVec;
data[0] = p1;
data[1] = p2;
data[2] = p3;


//return stringVec;
}

double Vec3D::dot(const Vec3D& rhs)
{
    double product = 0.0;

    product = (data[0] * rhs[0]) + (data[1] * rhs[1]) + (data[2] * rhs[2]);


    return product;
}