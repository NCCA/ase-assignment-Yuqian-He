#include<gtest/gtest.h>
#include"Particle.h"
#include"ParticleGenerator.h"

TEST(Generator,construct)
{
    auto g = particleGenerator(2);
    ASSERT_EQ(g.get_numParticles(),2);
    ASSERT_EQ(g.get_particlePosition(0).m_x,0);
    ASSERT_EQ(g.get_particlePosition(0).m_y,0);
    ASSERT_EQ(g.get_particlePosition(0).m_z,0);
    ASSERT_EQ(g.get_particlePosition(1).m_x,0);
    ASSERT_EQ(g.get_particlePosition(1).m_y,1);
    ASSERT_EQ(g.get_particlePosition(1).m_z,0);

    ASSERT_EQ(g.get_particleExtForce(0).m_x,0);
    ASSERT_EQ(g.get_particleExtForce(0).m_y,0);
    ASSERT_EQ(g.get_particleExtForce(0).m_z,0);
    ASSERT_EQ(g.get_particleExtForce(1).m_x,0);
    ASSERT_EQ(g.get_particleExtForce(1).m_y,0);
    ASSERT_EQ(g.get_particleExtForce(1).m_z,0);

    ASSERT_EQ(g.get_particleVelocity(0).m_x,0);
    ASSERT_EQ(g.get_particleVelocity(0).m_y,0);
    ASSERT_EQ(g.get_particleVelocity(0).m_z,0);
    ASSERT_EQ(g.get_particleVelocity(1).m_x,0);
    ASSERT_EQ(g.get_particleVelocity(1).m_y,0);
    ASSERT_EQ(g.get_particleVelocity(1).m_z,0);

    ASSERT_EQ(g.get_particleMass(0),10000);
    ASSERT_EQ(g.get_particleMass(1),10000);
    ASSERT_EQ(g.get_ifFixed(0),false);
}

TEST(Generator,ParticleMove)
{
    auto g = particleGenerator(2);
    g.set_particleExtForce(0,1.0f,1.0f,1.0f);
    std::cout<<g.get_particleProposedPosition(0).m_x<<'\n';
    std::cout<<g.get_particleProposedPosition(0).m_y<<'\n';
    std::cout<<g.get_particleProposedPosition(0).m_z<<'\n';
}
