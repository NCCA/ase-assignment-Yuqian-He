#include<iostream>
#include"Generator.h"
#include<fstream>
#include<sstream>
#include <ngl/Random.h>
#include<ngl/VAOFactory.h>
#include<ngl/SimpleVAO.h>

Generator::Generator(size_t _numParticle)
{
    m_particles.resize(_numParticle);
    
    int i=0;
    for(auto &p : m_particles)
    {
        p.m_position.set(0.0f,0.0f+i,0.0f);
        p.m_colour=ngl::Random::getRandomColour3();
        i++;
    }
    m_vao=ngl::VAOFactory::createVAO(ngl::simpleVAO,GL_POINTS);

}

void Generator::set_particlePosition(Particle &i_p, float _x, float _y, float _z)
{
    i_p.m_position.set(_x, _y, _z);
}

ngl::Vec3 Generator::get_particlePosition(Particle &o_p)
{
    return o_p.m_position;
}

void Generator::set_particleExtForce(Particle &i_p, float _x, float _y, float _z)
{
    i_p.m_extForce.set(_x, _y, _z);
}

ngl::Vec3 Generator::get_particleExtForce(Particle &o_p)
{
    return o_p.m_extForce;
}

ngl::Vec3 Generator::get_particleProposedPosition(Particle &o_p)
{
    return o_p.m_proposedPosition;
}

ngl::Vec3 Generator::get_particleVelocity(Particle &o_p)
{
    return o_p.m_velocity;
}

void Generator::set_particleMass(Particle &i_p, size_t mass)
{
    if(mass == 0) i_p.m_inverseMass=1;
    else i_p.m_inverseMass=1/mass;
}

size_t Generator::get_particleMass(Particle &o_p)
{
    if(o_p.m_inverseMass==0) return 10000;
    else return 1/o_p.m_inverseMass;
}

size_t Generator::get_numParticles() const
{
    return m_particles.size();
}

void Generator::update()
{
    //std::cout<<"update\n";
    float _dt=0.01;

    //  ngl::Vec3 gravity(0,-9.81f,0);
    // for(auto &p:m_particles)
    // {
    //     //direction=velocity
    //     p.m_velocity+=gravity*_dt*0.5f; //formula: dt_s=1/2*gravity*(dt_t)^2
    //     p.m_position+=p.m_velocity*_dt;
    // }

    //update the attribute of every particles
}

void Generator::render() const
{
    glPointSize(4);
    m_vao->bind();
    m_vao->setData(ngl::SimpleVAO::VertexData(m_particles.size()*sizeof(Particle), m_particles[0].m_position.m_x));
    m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(Particle),0);
    m_vao->setNumIndices(m_particles.size());
    m_vao->draw();
    m_vao->unbind();

}