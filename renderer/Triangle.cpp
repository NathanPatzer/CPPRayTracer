#include "Triangle.h"

//setting the verticies of the triangle
Triangle::Triangle(Vec3D a, Vec3D b, Vec3D c){
m_a = a;
m_b = b;
m_c = c;

createBoundingBox();

Vec3D cMax = boundingBox.maxPt;
Vec3D cMin = boundingBox.minPt;

//x
Vec3D center; 
center = cMax + cMin;
center = center / 2.0;

centroid = center;
}


//o +td = a + B(b-a) + G(c-a)
//have access to r.origin and r.direction
bool Triangle::closestHit( Ray r, double tMin, double tMax, HitStruct &hStruct){

double T;

double Beta;

double Gamma;

double M;


//initialize variables    
    double xa = m_a[0];
    double xb = m_b[0];
    double xc = m_c[0];

    double ya = m_a[1];
    double yb = m_b[1];
    double yc = m_c[1];

    double za = m_a[2];
    double zb = m_b[2];
    double zc = m_c[2];

    double xd = r.direction[0];
    double yd = r.direction[1];
    double zd = r.direction[2];

    double xe = r.origin[0];
    double ye = r.origin[1];
    double ze = r.origin[2];

double a = xa - xb;
double b = ya - yb;
double c = za - zb;
double d = xa - xc;
double e = ya - yc;
double f = za - zc;
double g = xd;
double h = yd;
double i = zd;
double j = xa - xe;
double k = ya - ye;
double l = za - ze;

//helpers
double ei = e*i;
double hf = h*f;
double gf = g*f;
double di = d*i;
double dh = d*h;
double eg = e*g;
double ak = a*k;
double jb = j*b;
double jc = j*c;
double al = a*l;
double bl = b*l;
double kc = k*c;

//compute M
	M = a*(ei - hf) + b*(gf - di) + c*(dh - eg);
//std::cout << M << "\n";
//compute T
	T = f*(ak - jb) + e*(jc - al) + d*(bl-kc);
	T = T/M;
	T = T * -1.0;
//std::cout << T << "\n";
//if (t<t0) or (t>t1) then
//return false
	if ( T < tMin || T > tMax){
    		return false;
	}
	else{
		//m_T = T;
		
	}

//compute Gamma
	Gamma = i*(ak-jb) + h*(jc-al) + g*(bl-kc);
	Gamma = Gamma/M;
	
//std::cout << Gamma << "\n";
//if (γ < 0) or (γ > 1) then
//return false
	if (Gamma < 0 || Gamma > 1){
    		return false;
	}

//compute Beta
	Beta = j*(ei - hf) + k*(gf-di) + l*(dh-eg);
	Beta = Beta/M;
	
//if (β < 0) or (β > 1 − γ) then
//return false

	if (Beta < 0 || Beta > (1-Gamma)){
   		 return false;
	}
hStruct.normal = calculateNormal(m_a,m_b,m_c);
hStruct.m_T = T;

hStruct.m_R = r;
hStruct.m_shapePtr = this;
return true;
}

Vec3D Triangle::calculateNormal(Vec3D v1, Vec3D v2, Vec3D v3)
{

	Vec3D A = v2 - v1;
	Vec3D B = v3 - v1;
	Vec3D normal = A.crossProduct(B);
	normal = normal.normalize();

return normal;
}

//finds minimum of three values passed in
double findMinimum(double a, double b, double c)
{
double min = std::min(a,std::min(b,c));

return min;
}

//finds maximum of three values passed in
double findMaximum(double a, double b, double c)
{
double max = std::max(a,std::max(b,c));

return max;
}

void Triangle::createBoundingBox()
{
Vec3D A = m_a;
Vec3D B = m_b;
Vec3D C = m_c;
//find minimum of bounding box
Vec3D min;

double minX = findMinimum(A[0],B[0],C[0]);
double minY = findMinimum(A[1],B[1],C[1]);
double minZ = findMinimum(A[2],B[2],C[2]);

min = Vec3D(minX,minY,minZ);

//find maximum of bounding box
Vec3D max;

double maxX = findMaximum(A[0],B[0],C[0]);
double maxY = findMaximum(A[1],B[1],C[1]);
double maxZ = findMaximum(A[2],B[2],C[2]);

max = Vec3D(maxX,maxY,maxZ);



boundingBox = AABoundingBox(min,max);
}

void Triangle::calculateBarycentric(double x, double y)
{

double Beta = implicitLine(m_a,m_c,x,y);
Beta = Beta / implicitLine(m_a,m_c,m_b[0],m_b[1]);

double Gamma = implicitLine(m_a,m_b,x,y);
Gamma = Gamma / implicitLine(m_a,m_b,m_c[0],m_c[1]);

double alpha = 1- Beta - Gamma;

m_Alpha = alpha;
m_Beta = Beta;
m_Gamma = Gamma;

}

double Triangle::implicitLine(Vec3D A, Vec3D B, double x, double y)
{

double val; 

val = (A[1] - B[1]) * x;



val = val + (B[0] - A[0]) * y;



val = val + (A[0] * B[1]) - (B[0] * A[1]);




return val;

}