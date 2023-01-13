#include "CoordSys.h"


//two argument constructor
 CoordSys::CoordSys(const Vec3D gaze, const Vec3D up)
 {
    
    //W
    m_W = -1.0 * gaze;
    m_W = m_W/m_W.length();
    
    //U
    m_U = up;
    m_U = m_U.crossProduct(m_W);
    m_U = m_U/m_U.length();
    
    //V
    m_V = m_W.crossProduct(m_U);
    m_V = m_V / m_V.length();
	
    
 }
