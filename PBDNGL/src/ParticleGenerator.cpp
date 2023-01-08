#include<iostream>
#include"ParticleGenerator.h"
#include<fstream>
#include<sstream>
#include <ngl/Random.h>
#include<ngl/VAOFactory.h>
#include<ngl/MultiBufferVAO.h>
#include<string>
#include<ngl/ShaderLib.h>

const float delta_t=0.005;

particleGenerator::particleGenerator(size_t _numParticle)
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
        m_positions[i].set(0.0f,0.0f-j*0.1,0.0f);
        m_colours[i]=ngl::Random::getRandomColour3();
        m_ifFixeds[i]=false;
        j++;
    }
    m_inverseMasses[0]=0;

    for(auto i=1; i<_numParticle;++i)
    {
        m_inverseMasses[i]=0.99;
    }

    m_vao = ngl::vaoFactoryCast<ngl::MultiBufferVAO>(ngl::VAOFactory::createVAO(ngl::multiBufferVAO,GL_LINES | GL_POINTS));
    particleGenerator::paint();
}

//write the set data for rendering
void particleGenerator::paint() const
{
    

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

    m_vao->setMode(GL_LINE_STRIP);
    //ngl::ShaderLib::setUniform("inColour", 1.0f,0.0f,0.0f,1.0f);
    //ngl::ShaderLib::setUniform("pointSize", 1.0f);
    m_vao->draw();

    m_vao->setMode(GL_POINTS);
    //ngl::ShaderLib::setUniform("inColour", 1.0f,1.0f,0.0f,1.0f);
    //ngl::ShaderLib::setUniform("pointSize", 6.0f);
    m_vao->draw();

    m_vao->unbind();

}

void particleGenerator::set_particlePosition(size_t _index, float _x, float _y, float _z)
{

    m_positions[_index].set(_x, _y, _z);
}

ngl::Vec3 particleGenerator::get_particlePosition(size_t _index)
{
    return m_positions[_index];
}

void particleGenerator::set_particleExtForce(size_t _index, float _x, float _y, float _z)
{
    m_extForces[_index]+={_x, _y, _z};
}

ngl::Vec3 particleGenerator::get_particleExtForce(size_t _index)
{
    return m_extForces[_index];
}

void particleGenerator::set_particleProposedPosition(size_t _index, float _x, float _y, float _z)
{
    m_proposedPositions[_index].set(_x, _y, _z);
}

//应该放在solver里
void particleGenerator::set_particleProposedPosition_b(size_t _index)
{
    
    auto acceleration = m_extForces[_index]*m_inverseMasses[_index];
    //std::cout<<o_p.m_extForce.m_x<<','<<o_p.m_extForce.m_y<<','<<o_p.m_extForce.m_y<<'\n';
    //std::cout<<acceleration.m_x<<','<<acceleration.m_y<<','<<acceleration.m_y<<'\n';
    m_velocities[_index] = m_velocities[_index]+delta_t*m_extForces[_index];
    //std::cout<<o_p.m_velocity.m_x<<','<<o_p.m_velocity.m_y<<','<<o_p.m_velocity.m_y<<'\n';
    m_proposedPositions[_index] = m_positions[_index]+delta_t*m_velocities[_index];
    //m_positions[_index] = m_positions[_index]+delta_t*m_velocities[_index];
    //std::cout<<m_positions[1].m_x<<','<<m_positions[1].m_y<<','<<m_positions[1].m_z<<'\n';
}

ngl::Vec3 particleGenerator::get_particleProposedPosition(size_t _index)
{
    return m_proposedPositions[_index];
}

ngl::Vec3 particleGenerator::get_particleVelocity(size_t _index)
{
    return m_velocities[_index];
}

void particleGenerator::set_particleDampVelocity(size_t _index, float damp)
{
    m_velocities[_index]*=damp;
}

void particleGenerator::set_particleVelocity(size_t _index,float _x, float _y, float _z)
{
    m_velocities[_index].set(_x, _y, _z);
}

void particleGenerator::set_particleMass(size_t _index, size_t mass)
{
    if(mass == 0) m_inverseMasses[_index]=1;
    else m_inverseMasses[_index]=1/mass;
}

size_t particleGenerator::get_particleInverseMass(size_t _index)
{
    return m_inverseMasses[_index];
}

bool particleGenerator::get_ifFixed(size_t _index) 
{
    return m_ifFixeds[_index];
}

size_t particleGenerator::get_numParticles() const
{
    return m_positions.size();
}

//改成引用！
void particleGenerator::update()
{
    //std::cout<<"***********************************************************"<<'\n';
    //calculate the proposed position
    for(size_t i=0; i<m_positions.size(); ++i)
    {
        if(m_ifFixeds[i] == false)
        {
            set_particleProposedPosition_b(i);
        }              
    }
 
    for(int i=0;i<10;++i)//为什么i越大越拉不动-->期望：回弹性应该越好
    {
        for(size_t i=0;i<m_positions.size()-1;i++)
        {
            distanceConstrain(i,0.1,0.5);
        }
    }

    for(int i=0; i<m_positions.size();++i)
    {
        m_velocities[i] = (m_proposedPositions[i]-m_positions[i])/delta_t;
        m_positions[i] = m_proposedPositions[i];
    }

    
}

void particleGenerator::render() const
{
    particleGenerator::paint();
}

//删掉！！！
void particleGenerator::distanceConstrain(size_t _index, float originalLength, float k)
{
    auto w1 = (-m_inverseMasses[_index])/(m_inverseMasses[_index]+m_inverseMasses[_index+1]);
    auto w2 = m_inverseMasses[_index+1]/(m_inverseMasses[_index]+m_inverseMasses[_index+1]);
    ngl::Vec3 delta_p1;
    ngl::Vec3 delta_p2;


    auto p1 = m_proposedPositions[_index];
    auto p2 = m_proposedPositions[_index+1];
   
    auto currentLength = sqrt(pow(p1.m_x-p2.m_x, 2)+pow(p1.m_y-p2.m_y,2)+pow(p1.m_z-p2.m_z,2));
    auto s1 = w1* (currentLength-originalLength)/currentLength;
    auto s2 = w2* (currentLength-originalLength)/currentLength;

    delta_p1 = s1*(p1-p2)*k;
    delta_p2 = s2*(p1-p2)*k;

    m_proposedPositions[_index]+=delta_p1;
    m_proposedPositions[_index+1]+=delta_p2;

    
}