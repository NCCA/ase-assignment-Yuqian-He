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
    int i = 0;
    
    for(auto &p : m_particles)
    {
        //initialize the attribute of every particles

        p.m_colour=ngl::Random::getRandomColour3();
    }

    //test render THIS IS WRONG
    m_particles[0].m_position.set(0.0f,0.0f,0.0f);
    m_particles[1].m_position.set(1.0f,0.0f,0.0f);   

    m_particles[0].m_position.set(0.0f,0.0f,0.0f);
    m_particles[5].m_position.set(0.0f,1.0f,0.0f);

    m_particles[1].m_position.set(1.0f,0.0f,0.0f);
    m_particles[2].m_position.set(2.0f,0.0f,0.0f);

    m_particles[1].m_position.set(1.0f,0.0f,0.0f);
    m_particles[4].m_position.set(1.0f,1.0f,0.0f);

    m_particles[3].m_position.set(2.0f,1.0f,0.0f);
    m_particles[2].m_position.set(2.0f,0.0f,0.0f);

    m_particles[3].m_position.set(2.0f,1.0f,0.0f);
    m_particles[4].m_position.set(1.0f,1.0f,0.0f);

    m_particles[4].m_position.set(1.0f,1.0f,0.0f);
    m_particles[5].m_position.set(0.0f,1.0f,0.0f);

    m_vao=ngl::VAOFactory::createVAO(ngl::simpleVAO,GL_LINES);

}

size_t Generator::numParticles() const
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