#ifndef SIMULATIONSOLVER_H_
#define SIMULATIONSOLVER_H_
#include<iostream>
#include"ParticleGenerator.h"
#include"Constrain.h"
#include "DistanceConstrain.h"
#include <typeinfo>

const float delta_t=0.005;
std::vector<std::shared_ptr<constrain>> test2;

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

void generateConstrain(std::vector<std::shared_ptr<constrain>> constrainTypes,std::vector<int> constrainType)
{
    for(int i=0;i<constrainType.size();++i)
    {
        if(constrainType[i] == 0)
        {
            //std::cout<<constrainType.size()<<'\n';
            auto dc = std::make_shared<distanceConstrain>(0.8);
            constrainTypes[i]=dc; 
            
        }
    }
    test2 = constrainTypes;
}

void projectConstrain(std::vector<std::shared_ptr<constrain>> constrainTypes,std::shared_ptr<particleGenerator> particle,float d, size_t steps)
{
    
    for(int j=0;j<steps;++j)
    {
        for(int i=0; i<particle->get_numParticles()-1;++i)
        {
            //std::cout<<"!!!!"<<'\n';
            //std::cout<<constrainTypes[0]->stiffness<<'\n';
            for(int k=0;k<constrainTypes.size();++k)
            {
                std::cout<<i<<'\n';
                constrainTypes[k].get()->projection(particle,i,d);
                //std::cout<<typeid(constrainTypes[k]).name()<<'\n';
                //std::cout<<constrainTypes[k]->stiffness<<'\n';
            }
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
    //std::vector<std::shared_ptr<constrain>> constrainTypes;
    std::vector<int> test = {0};
    //constrainTypes.resize(test.size());
    test2.resize(test.size());
    generateConstrain(test2,test);
    //constrainTypes=test2;
    //std::cout<<constrainTypes[0]->stiffness<<'\n';
    //std::cout<<typeid(constrainTypes[0]).name()<<'\n';
    dampVelocity(particle,damp);
    makeProposedPosition(particle);
    projectConstrain(test2,particle,d,steps);
    finalizeUpdate(particle);

}

#endif
