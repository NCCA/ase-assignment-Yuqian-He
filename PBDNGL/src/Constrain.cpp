#include<iostream>
#include<ngl/Vec3>
#include<cmath>

float pointLength(ngl::Vec3 p1, ngl::Vec3 p2)
{
    float length = sqrt(pow(p2.m_x-p1.m_x, 2)+pow(p2.m_y-p1.m_y,2)+pow(p2.m_z-p1.m_z,2));
}

