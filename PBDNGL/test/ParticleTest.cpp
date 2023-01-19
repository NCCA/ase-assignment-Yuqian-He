#include<gtest/gtest.h>
#include"ParticleGenerator.h"
#include<iostream>
#include<ngl/Vec3.h>
#include<cmath>
#include"CollisionConstrain.h"
#include"Constrain.h"
#include"DistanceConstrain.h"


TEST(Generator,construct)
{

    std::unique_ptr<particleGenerator> m_ParticleGenerator;
    m_ParticleGenerator=std::make_unique<particleGenerator>(1,1);

    ASSERT_EQ(m_ParticleGenerator->get_particlePosition(0).m_x,0);
    ASSERT_EQ(m_ParticleGenerator->get_particlePosition(0).m_y,0);
    ASSERT_EQ(m_ParticleGenerator->get_particlePosition(0).m_z,0);
    ASSERT_EQ(m_ParticleGenerator->get_particleExtForce(0).m_x,0);
    ASSERT_EQ(m_ParticleGenerator->get_particleExtForce(0).m_y,0);
    ASSERT_EQ(m_ParticleGenerator->get_particleExtForce(0).m_z,0);

}

TEST(Generator, accessor)
{
    std::unique_ptr<particleGenerator> p;
    p=std::make_unique<particleGenerator>(1,1);
    p->set_particlePosition(1,1.0f,1.0f,1.0f);
    ASSERT_EQ(p->get_particlePosition(1).m_x,1.0f);
    ASSERT_EQ(p->get_particlePosition(1).m_y,1.0f);
    ASSERT_EQ(p->get_particlePosition(1).m_z,1.0f);
    p->set_particleExtForce(1,2.0f,1.0f,1.0f);
    p->set_particleExtForce(1,2.0f,1.0f,1.0f);
    ASSERT_EQ(p->get_particleExtForce(1).m_x,4.0f);
    ASSERT_EQ(p->get_particleExtForce(1).m_y,2.0f);
    ASSERT_EQ(p->get_particleExtForce(1).m_z,2.0f);
    p->set_particleVelocity(1,2.0f,1.0f,1.0f);
    p->set_particleDampVelocity(1,0.5f);
    ASSERT_EQ(p->get_particleVelocity(1).m_x,1.0f);
    ASSERT_EQ(p->get_particleVelocity(1).m_y,0.5f);
    ASSERT_EQ(p->get_particleVelocity(1).m_z,0.5f);
}


