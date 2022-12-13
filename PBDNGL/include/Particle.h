#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <ngl/Vec3.h>
#include<cstddef>

struct Particle
{
    ngl::Vec3 m_position;
    ngl::Vec3 m_extForce;
    ngl::Vec3 m_proposedPosition;
    ngl::Vec3 m_colour;
    ngl::Vec3 m_velocity={0.0f,0.0f,0.0f};
    size_t m_inverseMass;
};

#endif