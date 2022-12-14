#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <ngl/Vec3.h>
#include<cstddef>

struct Particle
{
    ngl::Vec3 m_position;
    ngl::Vec3 m_extForce={0.0f,0.0f,0.0f};
    ngl::Vec3 m_proposedPosition;
    ngl::Vec3 m_colour;
    ngl::Vec3 m_velocity={0.0f,0.0f,0.0f};
    float m_inverseMass=0.5;
    bool m_ifFixed=false;
};

#endif