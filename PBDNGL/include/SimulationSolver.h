#include<iostream>
#include"ParticleGenerator.h"
#include"Constrain.h"


const float delta_t=0.005;

void dampVelocity(std::shared_ptr<particleGenerator> particle,float damp)
{
    for(int i=0; i<particle->get_numParticles();++i)
    {
        particle->set_particleDampVelocity(i,damp);
    }
}

void makeProposedPosition(std::shared_ptr<particleGenerator> particle)
{
    for(int i=0; i<particle->get_numParticles();++i)
    {
        auto acceleration=particle->get_particleExtForce(i)*particle->get_particleInverseMass(i);
        ngl::Vec3 delta = delta_t*particle->get_particleExtForce(i);

        auto _x=delta.m_x+particle->get_particleVelocity(i).m_x;
        auto _y=delta.m_y+particle->get_particleVelocity(i).m_y;
        auto _z=delta.m_z+particle->get_particleVelocity(i).m_z;

        particle->set_particleVelocity(i,_x,_y,_z);

        ngl::Vec3 h=particle->get_particlePosition(i)+delta*particle->get_particleVelocity(i);
        particle->set_particleProposedPosition(i,h.m_x,h.m_y,h.m_z);
    }

}

void projectConstrain(std::shared_ptr<particleGenerator> particle,float d, size_t steps)
{
    
    for(int i=0;i<steps;++i)
    {
        for(int j=0; j<particle->get_numParticles()-1;++j)
        {
            constrain c;
            c.distanceConstrain(particle, j, d);
        }
    }
    
}

void finalizeUpdate(std::shared_ptr<particleGenerator> particle)
{
    for(int i=0; i<particle->get_numParticles();++i)
    {
        ngl::Vec3 p=particle->get_particleProposedPosition(i)-particle->get_particlePosition(i);
        particle->set_particleVelocity(i,(p/delta_t).m_x,(p/delta_t).m_y,(p/delta_t).m_z);

        particle->set_particlePosition(i,particle->get_particleProposedPosition(i).m_x,
                                                    particle->get_particleProposedPosition(i).m_y,
                                                    particle->get_particleProposedPosition(i).m_z);
    }
}

void PBD(std::shared_ptr<particleGenerator> particle,float damp,float d,size_t steps)
{
    //std::cout<<particle->get_particleInverseMass(2)<<'\n';

    dampVelocity(particle,damp);
    makeProposedPosition(particle);
    projectConstrain(particle,d,steps);
    finalizeUpdate(particle);

}
