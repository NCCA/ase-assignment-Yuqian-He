#include "DistanceConstrain.h"
#include <iostream>

distanceConstrain::distanceConstrain(){}

float distanceConstrain::get_stiffness()
{
    return stiffness;
}

void distanceConstrain::projection(std::shared_ptr<particleGenerator> particle, size_t _index, float originalLength)
{
    if(_index == particle->get_numParticles()-1) return;
    auto w1=(-particle->get_particleInverseMass(_index)) / (particle->get_particleInverseMass(_index)+particle->get_particleInverseMass(_index+1));
    auto w2=particle->get_particleInverseMass(_index+1) / (particle->get_particleInverseMass(_index)+particle->get_particleInverseMass(_index+1));

    ngl::Vec3 delta_p1;
    ngl::Vec3 delta_p2;

    auto p1=particle->get_particleProposedPosition(_index);
    auto p2=particle->get_particleProposedPosition(_index+1);

    float currentLength=sqrt(pow(p1.m_x-p2.m_x, 2)+pow(p1.m_y-p2.m_y,2)+pow(p1.m_z-p2.m_z,2));



    auto s1 = w1* (currentLength-originalLength)/currentLength;
    auto s2 = w2* (currentLength-originalLength)/currentLength;


    delta_p1 = s1*(p1-p2)*stiffness;
    delta_p2 = s2*(p1-p2)*stiffness;

    

    auto _x1 = particle->get_particleProposedPosition(_index).m_x+delta_p1.m_x;
    auto _y1 = particle->get_particleProposedPosition(_index).m_y+delta_p1.m_y;
    auto _z1 = particle->get_particleProposedPosition(_index).m_z+delta_p1.m_z;

    auto _x2 = particle->get_particleProposedPosition(_index+1).m_x+delta_p2.m_x;
    auto _y2 = particle->get_particleProposedPosition(_index+1).m_y+delta_p2.m_y;
    auto _z2 = particle->get_particleProposedPosition(_index+1).m_z+delta_p2.m_z;

    particle->set_particleProposedPosition(_index,_x1,_y1,_z1);
    particle->set_particleProposedPosition(_index+1,_x2,_y2,_z2);
}
