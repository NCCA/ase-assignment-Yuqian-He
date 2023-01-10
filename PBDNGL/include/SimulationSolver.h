#ifndef SIMULATIONSOLVER_H_
#define SIMULATIONSOLVER_H_
#include<iostream>
#include"ParticleGenerator.h"
#include"Constrain.h"

constrain c;
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
        ngl::Vec3 delta = delta_t*particle->get_particleExtForce(i) + particle->get_particleVelocity(i);
        particle->set_particleVelocity(i,delta.m_x,delta.m_y,delta.m_z);
        ngl::Vec3 h=particle->get_particlePosition(i)+delta_t*particle->get_particleVelocity(i);
        particle->set_particleProposedPosition(i,h.m_x,h.m_y,h.m_z);
    }

}

void projectConstrain(std::shared_ptr<particleGenerator> particle,float d, size_t steps)
{
    
    for(int j=0;j<steps;++j)
    {
        for(int i=0; i<particle->get_numParticles()-1;++i)
        {
            auto w1=(-particle->get_particleInverseMass(i)) / (particle->get_particleInverseMass(i)+particle->get_particleInverseMass(i+1));
            auto w2=particle->get_particleInverseMass(i+1) / (particle->get_particleInverseMass(i)+particle->get_particleInverseMass(i+1));

            ngl::Vec3 delta_p1;
            ngl::Vec3 delta_p2;

            auto p1=particle->get_particleProposedPosition(i);
            auto p2=particle->get_particleProposedPosition(i+1);

            float currentLength=sqrt(pow(p1.m_x-p2.m_x, 2)+pow(p1.m_y-p2.m_y,2)+pow(p1.m_z-p2.m_z,2));



            auto s1 = w1* (currentLength-d)/currentLength;
            auto s2 = w2* (currentLength-d)/currentLength;


            delta_p1 = s1*(p1-p2)*0.9;
            delta_p2 = s2*(p1-p2)*0.9;

            

            auto _x1 = particle->get_particleProposedPosition(i).m_x+delta_p1.m_x;
            auto _y1 = particle->get_particleProposedPosition(i).m_y+delta_p1.m_y;
            auto _z1 = particle->get_particleProposedPosition(i).m_z+delta_p1.m_z;

            auto _x2 = particle->get_particleProposedPosition(i+1).m_x+delta_p2.m_x;
            auto _y2 = particle->get_particleProposedPosition(i+1).m_y+delta_p2.m_y;
            auto _z2 = particle->get_particleProposedPosition(i+1).m_z+delta_p2.m_z;

            particle->set_particleProposedPosition(i,_x1,_y1,_z1);
            particle->set_particleProposedPosition(i+1,_x2,_y2,_z2);
          
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
    //std::cout<<particle->get_particleProposedPosition(19).m_y<<'\n';
    dampVelocity(particle,damp);
    makeProposedPosition(particle);
    //std::cout<<particle->get_particlePosition(2).m_y<<'\n';
    //std::cout<<particle->get_particlePosition(1).m_y<<'\n';
    std::cout<<particle->get_particleProposedPosition(19).m_y<<"!!!!!!"<<'\n';
    projectConstrain(particle,d,steps);
    finalizeUpdate(particle);

}

#endif
