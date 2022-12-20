#include<iostream>
#include"Generator.h"
#include<fstream>
#include<sstream>
#include <ngl/Random.h>
#include<ngl/VAOFactory.h>
#include<ngl/MultiBufferVAO.h>
#include<string>

const float delta_t=0.005;

Generator::Generator(size_t _numParticle)
{
    m_positions.resize(_numParticle);
    m_extForces.resize(_numParticle);
    m_proposedPositions.resize(_numParticle);
    m_colours.resize(_numParticle);
    m_velocities.resize(_numParticle);
    m_inverseMasses.resize(_numParticle);
    m_ifFixeds.resize(_numParticle);
    
    int j=0;
    for(auto i=0; i<_numParticle;++i)
    {
        m_positions[i].set(0.0f,0.0f+i,0.0f);
        m_colours[i]=ngl::Random::getRandomColour3();
        j++;
    }
    m_vao=ngl::vaoFactoryCast<ngl::MultiBufferVAO>(ngl::VAOFactory::createVAO(ngl::multiBufferVAO,GL_POINTS));
    m_vao->bind();
    //buffer 0 is position data
    m_vao->setData(ngl::MultiBufferVAO::VertexData(m_positions.size()*sizeof(ngl::Vec3),m_positions[0].m_x));
    m_vao->setVertexAttributePointer(0,3,GL_FLOAT,0,0);

    //buffer 1 is exforce data
    m_vao->setData(ngl::MultiBufferVAO::VertexData(m_extForces.size()*sizeof(ngl::Vec3),m_extForces[0].m_x));
    m_vao->setVertexAttributePointer(1,3,GL_FLOAT,0,0);

    //buffer 2 is proposedPosition data
    m_vao->setData(ngl::MultiBufferVAO::VertexData(m_proposedPositions.size()*sizeof(ngl::Vec3),m_proposedPositions[0].m_x));
    m_vao->setVertexAttributePointer(2,3,GL_FLOAT,0,0);

    //buffer 3 is colour data
    m_vao->setData(ngl::MultiBufferVAO::VertexData(m_colours.size()*sizeof(ngl::Vec3),m_colours[0].m_x));
    m_vao->setVertexAttributePointer(3,3,GL_FLOAT,0,0);

    //buffer 4 is velocity data
    m_vao->setData(ngl::MultiBufferVAO::VertexData(m_velocities.size()*sizeof(ngl::Vec3),m_velocities[0].m_x));
    m_vao->setVertexAttributePointer(4,3,GL_FLOAT,0,0);

    m_vao->setNumIndices(m_positions.size());
    m_vao->unbind();
}

void Generator::set_particlePosition(size_t _index, float _x, float _y, float _z)
{

    m_positions[_index].set(_x, _y, _z);
}

ngl::Vec3 Generator::get_particlePosition(size_t _index)
{
    return m_positions[_index];
}

void Generator::set_particleExtForce(size_t _index, float _x, float _y, float _z)
{
    m_extForces[_index].set(_x, _y, _z);
}

ngl::Vec3 Generator::get_particleExtForce(size_t _index)
{
    return m_extForces[_index];
}

void Generator::set_particleProposedPosition(size_t _index)
{
    
    auto acceleration = m_extForces[_index]*m_inverseMasses[_index];
    //std::cout<<o_p.m_extForce.m_x<<','<<o_p.m_extForce.m_y<<','<<o_p.m_extForce.m_y<<'\n';
    //std::cout<<acceleration.m_x<<','<<acceleration.m_y<<','<<acceleration.m_y<<'\n';
    m_velocities[_index] = m_velocities[_index]+delta_t*m_extForces[_index];
    //std::cout<<o_p.m_velocity.m_x<<','<<o_p.m_velocity.m_y<<','<<o_p.m_velocity.m_y<<'\n';
    m_positions[_index] = m_positions[_index]+delta_t*m_velocities[_index];
}

ngl::Vec3 Generator::get_particleProposedPosition(size_t _index)
{
    return m_proposedPositions[_index];
}

ngl::Vec3 Generator::get_particleVelocity(size_t _index)
{
    return m_velocities[_index];
}

void Generator::set_particleMass(size_t _index, size_t mass)
{
    if(mass == 0) m_inverseMasses[_index]=1;
    else m_inverseMasses[_index]=1/mass;
}

size_t Generator::get_particleMass(size_t _index)
{
    if(m_inverseMasses[_index]==0) return 10000;
    else return 1/m_inverseMasses[_index];
}

bool Generator::get_ifFixed(size_t _index) 
{
    return m_ifFixeds[_index];
}

size_t Generator::get_numParticles() const
{
    return m_positions.size();
}

void Generator::update()
{
    for(size_t i=0; i<m_positions.size(); ++i)
    {
        set_particleProposedPosition(i);
        std::cout<<get_particleProposedPosition(i).m_x<<','<<get_particleProposedPosition(i).m_y<<','<<get_particleProposedPosition(i).m_z<<'\n';
    }


    //float _dt=0.01;

    //update the attribute of every particles
}

void Generator::render() const
{
    glPointSize(4);
    m_vao->bind();
    m_vao->setData(0,ngl::MultiBufferVAO::VertexData(m_positions.size()*sizeof(ngl::Vec3), m_positions[0].m_x));
    //m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(Particle),0);
    //m_vao->setNumIndices(m_particles.size());
    m_vao->draw();
    m_vao->unbind();

}