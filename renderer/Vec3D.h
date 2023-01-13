#pragma once

#include <cassert>
#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>


    class Vec3D 
    {
    public:
        Vec3D(); // default
        Vec3D( const double x, const double y, const double z );
        ~Vec3D() {}

        // Copy Constructor
        Vec3D( const Vec3D& v );

        // Index operator for getting
        const double operator[](const int idx) const
        {
            assert( idx >= 0 && idx < 3 );
            return data[idx];
        }
        
        // Index operator for setting
        double& operator[](const int idx)
        {
            assert( idx >= 0 && idx < 3 );
            return data[idx];
        }
        
        // Assignment operator
        Vec3D &operator=(const Vec3D &rhs)
        {
            // from a function standpoint, this looks like this:
            // a.operator=(b)
            data[0] = rhs[0];
            data[1] = rhs[1];
            data[2] = rhs[2];
            return *this;
        }

        double dot(const Vec3D& rhs);

        Vec3D normalize();

        Vec3D crossProduct(const Vec3D& rhs);

        Vec3D &operator+=(const Vec3D &rhs);

        void operator=(const std::string string);
        
        Vec3D &operator*(const Vec3D &rhs);
        // provide function declaration for length of vector
        double length(void) const
        {
            return sqrt( data[0]*data[0] + data[1]*data[1] + data[2]*data[2] );
        }

        //function for printing a Vec3D
        void print();

        
    private:

        std::vector< double > data;  // you need to initialize this in constructor
        
    };



// Non-member + operator -- takes two arguments
Vec3D operator+(const Vec3D& lhs, const Vec3D& rhs);
Vec3D operator*(const double lhs, const Vec3D& rhs);
Vec3D operator/(const Vec3D& lhs, const double rhs);
Vec3D operator-(const Vec3D& lhs,const Vec3D& rhs);