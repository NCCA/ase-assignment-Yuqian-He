#ifndef SIMULATIONSOLVER_H_
#define SIMULATIONSOLVER_H_
#include<iostream>
#include"ParticleGenerator.h"
#include"Constrain.h"
#include "DistanceConstrain.h"
#include "CollisionConstrain.h"
#include <typeinfo>
#include <ngl/Transformation.h>

const float delta_t=0.005;
std::vector<std::shared_ptr<constrain>> test2;
float stiffness=0.2;
float collisionStiffness=0.9;
float minDistance;

// void setWorldPosition(std::shared_ptr<particleGenerator> particle)
// {
//     for(int i=0; i<particle->get_numParticles();++i)
//     {
//         particle->set_worldPosition(i);
//     }
// }

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

void generateConstrain(std::vector<std::shared_ptr<constrain>> constrainTypes,std::vector<int> constrainType,
                        std::shared_ptr<ngl::Obj> mesh,ngl::Transformation cube_model,
                        ngl::Mat4 m_mouseGlobalTX)
{
    for(int i=0;i<constrainType.size();++i)
    {
        if(constrainType[i] == 0)
        {
            auto dc = std::make_shared<distanceConstrain>(stiffness);
            constrainTypes[i]=dc; 
            
        }
        if(constrainType[i] == 1)
        {
            auto cc = std::make_shared<collisionConstrain>(mesh,cube_model,m_mouseGlobalTX,collisionStiffness);
            constrainTypes[i]=cc;
            //minDistance=cc->get_minDistance();
        }
    }
    test2 = constrainTypes;
}

void projectConstrain(std::vector<std::shared_ptr<constrain>> constrainTypes,std::shared_ptr<particleGenerator> particle,float d, size_t steps)
{
    
    for(int j=0;j<steps;++j)
    {
        for(int i=0; i<particle->get_numParticles();++i)
        {
            for(int k=0;k<constrainTypes.size();++k)
            {
                constrainTypes[k].get()->projection(particle,i,d);
            }
        }
    }
    
}

void finalizeUpdate(std::shared_ptr<particleGenerator> particle)
{

    for(int i=0; i<particle->get_numParticles();++i)
    {
        if(particle->get_ifCollider(i)==true)
        {
            //std::cout<<"!!!!!"<<'\n';
            auto move=(-particle->get_particleVelocity(i))*0.02;
            particle->set_particleVelocity(i,0,0,0);
            auto proPosition=particle->get_particleProposedPosition(i)+move;
            particle->set_particleProposedPosition(i,proPosition.m_x,proPosition.m_y,proPosition.m_z);
        }else
        {
            ngl::Vec3 p=particle->get_particleProposedPosition(i)-particle->get_particlePosition(i);
            particle->set_particleVelocity(i,(p/delta_t).m_x,(p/delta_t).m_y,(p/delta_t).m_z);
        }   
        particle->set_particlePosition(i,particle->get_particleProposedPosition(i).m_x,
                                            particle->get_particleProposedPosition(i).m_y,
                                            particle->get_particleProposedPosition(i).m_z);     
    }
}

void PBD(std::shared_ptr<particleGenerator> particle,float damp,float d,
        size_t steps,std::shared_ptr<ngl::Obj> mesh,ngl::Transformation cube_model,
        ngl::Mat4 m_mouseGlobalTX)
{
    std::vector<int> test = {0,1};
    test2.resize(test.size());
    generateConstrain(test2,test,mesh,cube_model,m_mouseGlobalTX);
    dampVelocity(particle,damp);
    makeProposedPosition(particle);
    projectConstrain(test2,particle,d,steps);
    finalizeUpdate(particle);
    //setWorldPosition(particle);
}

float get_stiffness()
{
    return stiffness;
}

#endif
