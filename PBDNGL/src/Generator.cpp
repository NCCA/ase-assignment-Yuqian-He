#include<iostream>
#include"Generator.h"
#include<fstream>
#include<sstream>
#include <ngl/Random.h>
#include<ngl/VAOFactory.h>
#include<ngl/SimpleVAO.h>
#include<string>

const float delta_t=0.005;

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

void Generator::set_particleProposedPosition(Particle &o_p)
{
    
    auto acceleration = o_p.m_extForce*o_p.m_inverseMass;
    //std::cout<<o_p.m_extForce.m_x<<','<<o_p.m_extForce.m_y<<','<<o_p.m_extForce.m_y<<'\n';
    //std::cout<<acceleration.m_x<<','<<acceleration.m_y<<','<<acceleration.m_y<<'\n';
    o_p.m_velocity = o_p.m_velocity+delta_t*o_p.m_extForce;
    //std::cout<<o_p.m_velocity.m_x<<','<<o_p.m_velocity.m_y<<','<<o_p.m_velocity.m_y<<'\n';
    o_p.m_proposedPosition = o_p.m_position+delta_t*o_p.m_velocity;
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

bool Generator::get_ifFixed(Particle &o_p) 
{
    return o_p.m_ifFixed;
}

size_t Generator::get_numParticles() const
{
    return m_particles.size();
}

void Generator::update()
{
    for(auto &p : m_particles)
    {
        set_particleProposedPosition(p);
        std::cout<<get_particleProposedPosition(p).m_x<<','<<get_particleProposedPosition(p).m_y<<','<<get_particleProposedPosition(p).m_z<<'\n';
    }


    //float _dt=0.01;

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