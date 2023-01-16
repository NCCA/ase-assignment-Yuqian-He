#include<gtest/gtest.h>
#include"ParticleGenerator.h"
#include<iostream>
#include<ngl/Vec3.h>
#include<cmath>


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


